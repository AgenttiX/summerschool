#!/usr/bin/env python3

# module load cray-python/3.11.7

import matplotlib.pyplot as plt
import pandas as pd


def main():
    df = pd.read_csv(
        "metrics.csv",
        # header=0,
        engine="c"
    )
    df.drop(
        columns=[
            "Index", "KernelName", "gpu-id", "queue-id", "queue-index", "pid", "tid", "grd", "wgr", "lds", "scr",
            "arch_vgpr", "accum_vgpr", "sgpr", "wave_size", "sig", "obj"
        ],
        inplace=True
    )
    df.drop([0], inplace=True)
    df.rename(
        columns={
            "TCC_EA_RDREQ_sum": "Global reads",
            "TCC_EA_RDREQ_32B_sum": "Global 32B reads",
            "TCP_TCC_READ_REQ_sum": "L1 -> L2 reads",
        },
        inplace=True
    )
    df["Stride"] = 2**df.index - 1
    print(df)

    fig = plt.figure()
    ax = fig.add_subplot()
    ax.plot(df["Stride"], df["Global reads"], label="Global reads")
    ax.plot(df["Stride"], df["Global 32B reads"], label="Global 32B reads")
    ax.plot(df["Stride"], df["L1 -> L2 reads"], label="L1 -> L2 reads")
    ax.set_xscale("log")
    ax.set_xlabel("Stride (2^n - 1)")
    ax.set_ylabel("Count")
    ax.legend()
    fig.savefig("metrics.png")


if __name__ == "__main__":
    main()
