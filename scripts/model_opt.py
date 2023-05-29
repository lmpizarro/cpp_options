import numpy as np
from scipy.stats import norm
from dataclasses import dataclass


@dataclass
class Option:
    S: float
    K: float
    r: float
    sg: float
    T: float
    t: float = 0

    def set(self, S, K, r, sg, T, t):
        self.S = S
        self.K = K
        self.r = r
        self.sg = sg
        self.T = T
        self.t = T


def d1(S, K, r, sg, T, t):
    return (np.log(S / K) + (r + 0.5 * sg * sg) * (T - t)) / (sg * np.sqrt(T - t))


def d2(S, K, r, sg, T, t):
    return d1(S, K, r, sg, T, t) - sg * np.sqrt(T - t)


def call(S, K, r, sg, T, t):
    return S * norm(0, 1).cdf(d1(S, K, r, sg, T, t)) - K * np.exp(-r * (T - t)) * norm(
        0, 1
    ).cdf(d2(S, K, r, sg, T, t))


def put(S, K, r, sg, T, t):
    return call(S, K, r, sg, T, t) - S + K * np.exp(-r * (T - t))


def deltaC(S, K, r, sg, T, t):
    return norm(0, 1).cdf(d1(S, K, r, sg, T, t))


def deltaP(S, K, r, sg, T, t):
    return deltaC(S, K, r, sg, T, t) - 1


def noise(s=1, c=0.1):
    return s + c * norm(0, 1).rvs(1)[0]


def pSin(i, S0, pct, days):
    return S0 * (1 + pct * np.sin(2 * np.pi * i / days))


def sgSin(i, sg0, pct, days):
    return sg0 * (1 - pct * np.sin(2 * np.pi * i / days))


def log(i, delta, s, shares, FlowCash, sigma):
    print(
        f"{i} delta: {round(delta,2):4.2f} price: {round(s,2):8.2f} shares: {round(shares,2):4.2f} flow {round(FlowCash,2):4.2f} sigma {round(sigma,2):4.2f}"
    )


def simulate_straddle():
    months = 1
    T = months / 12
    days = int(months * 20)
    S0 = 100
    K = 100
    r = 0.04
    sigma0 = 0.3
    tipoOpcion = "C"
    tipoPos = "L"  # 'S'
    sigTipo = -1 if tipoOpcion == "C" else 1

    opt = Option(S=S0, K=K, r=r, sg=sigma0, T=months / 12)

    R = noise(r)
    DeltaCi = deltaC(**opt.__dict__)
    DeltaPi = deltaP(**opt.__dict__)
    Calli = call(**opt.__dict__)
    Puti = put(**opt.__dict__)
    DeltaTi = DeltaPi + DeltaCi

    AccumCashShares = -S0 * DeltaTi
    cashShares = 0
    Cash = Calli
    log(0, DeltaTi, S0, cashShares, AccumCashShares, sigma0)
    pp = []
    pc = [(T, Calli + Puti), (T, AccumCashShares)]
    for i in range(1, days):
        R = noise(r, 0)
        f = i / days
        s = pSin(i, S0, 0.05, days)
        sigma = sgSin(i, sigma0, 0.1, days)

        # opt.set(s, K, R, sigma, T, f * T)
        DeltaC = deltaC(s, K, R, sigma, T, f * T)
        DeltaP = deltaP(s, K, R, sigma, T, f * T)
        DeltaT = DeltaC + DeltaP

        cashShares = -s * ((DeltaC - DeltaCi) + (DeltaP - DeltaPi))
        pc.append((T - f * T, cashShares))
        AccumCashShares += cashShares
        log(i, DeltaT, s, cashShares, AccumCashShares, sigma)
        DeltaCi = DeltaC
        DeltaPi = DeltaP
    total = 0
    for e in pc:
        total += e[1] * np.exp(e[0] * r)

    print(total)


def heston_milstein():
    months = 1
    days = 21 * months
    N = int(days)

    rho = 0.5
    zv = norm(0, 1).rvs(N)
    zs = norm(0, 1).rvs(N)
    zs = rho * zv + np.sqrt(1 - rho * rho) * zs

    v0 = 0.3
    s0 = 100
    theta = 0.1
    kappa = 42
    dt = 1 / 252
    sgm = 0.0
    r = 0.04
    res = np.zeros(N)
    res[0] = s0
    for i in range(1, N):
        v1 = (
            v0
            + kappa * (theta - v0) * dt
            + sgm * zv[i] * np.sqrt(v0 * dt)
            + 0.25 * sgm * sgm * dt * (zv[i] * zv[i] - 1)
        )
        s1 = s0 * (1 + r * dt + np.sqrt(v0 * dt) * zs[i]) + 0.25 * s0 * s0 * dt * (
            zs[i] * zs[i] - 1
        )
        v0 = max(0, v1)
        s0 = s1
        res[i] = s1

    print(res)


class Heston:
    def __init__(self, rho=0.8, kappa=21, theta=0.1, sigma=0.3, r=0.09, N=1) -> None:
        self.rho = rho
        self.kappa = kappa
        self.theta = theta
        self.sigma = sigma
        self.N: int = N
        self.zv = norm(0, 1).rvs(self.N)
        self.zs = norm(0, 1).rvs(self.N)
        self.zs = self.rho * self.zv + np.sqrt(1 - self.rho * self.rho) * self.zs
        self.r = r
        self.v0 = 0
        self.s0 = 0
        self.dt = 0

    def gen_unif(self):
        self.zv = norm(0, 1).rvs(self.N)
        self.zs = norm(0, 1).rvs(self.N)
        self.zs = self.rho * self.zv + np.sqrt(1 - self.rho * self.rho) * self.zs

    def set_model(self, v0, s0, dt):
        self.v0 = v0
        self.s0 = s0
        self.dt = dt

    def run(self):
        res = np.zeros(2 * self.N).reshape(2, self.N)
        res[0][0] = self.v0
        res[1][0] = self.s0
        self.gen_unif()
        for i in range(1, self.N):
            res[0][i] = max(
                0,
                res[0][i - 1]
                + self.kappa * (self.theta - res[0][i - 1]) * self.dt
                + self.sigma * self.zv[i] * np.sqrt(res[0][i - 1] * self.dt)
                + (0.25
                * np.power(self.sigma, 2)
                * self.dt
                * (np.power(self.zv[i], 2) - 1)),
            )
            res[1][i] = res[1][i - 1] * (
                1 + self.r * self.dt + np.sqrt(res[0][i - 1] * self.dt) * self.zs[i]
            )
            +0.25 * np.power(res[1][i - 1], 2) * self.dt * (
                np.power(self.zs[i], 2) - 1
            )
        return res


def test_class():
    months = 1
    days = 21 * months
    N = int(days)
    dt = 1 / 252

    hst = Heston(kappa=21, theta=0.2, sigma=.3, r=0.04, N=N)
    hst.set_model(v0=0.2, s0=100, dt=dt)

    M = 100
    res = np.zeros(N * M).reshape(M, N)

    def assign(arr, j):
        res[j] = arr

    [assign(hst.run()[1], j) for j in range(M)]

    print(np.mean(res, axis=0))

    print(res)


test_class()
