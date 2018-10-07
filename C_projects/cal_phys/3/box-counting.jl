{
 "cells": [
  {
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    "<h2>盒计数法计算分形维数</h2>"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": [
    "using PyPlot\n",
    "using DelimitedFiles\n",
    "k = readdlm(\"box-counting.txt\",'\\t')\n",
    "r = k'[1,:]\n",
    "N = k'[2,:]\n",
    "n = length(r)\n",
    "r = log.(r)\n",
    "N = log.(N)\n",
    "r̄ = sum(r)/n\n",
    "N̄ = sum(N)/n\n",
    "a = (r'*N-n*r̄*N̄)/(r'*r-n*r̄^2)\n",
    "b = N̄ - a*r̄\n",
    "R_square = (r'*N-n*r̄*N̄)^2/((r'*r-n*r̄^2)*(N'*N-n*N̄^2))\n",
    "println(\"y = ax + b:\\n\",\"a = \",a,\"\\nb = \",b,\"\\nR^2 =\",R_square)"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": [
    "fig2 = figure(figsize=[10, 10])\n",
    "grid(\"on\")\n",
    "title(\"box-counting\\ndim = $a\")\n",
    "xlabel(\"ln(r)\")\n",
    "ylabel(\"ln(N)\")\n",
    "scatter(r,N,s=10)\n",
    "x = 0:7\n",
    "plot(x,a*x.+b,c=\"orange\")\n",
    "savefig(\"./[336]1box-counting.png\")"
   ]
  }
 ],
 "metadata": {
  "kernelspec": {
   "display_name": "Julia 1.0.0",
   "language": "julia",
   "name": "julia-1.0"
  },
  "language_info": {
   "file_extension": ".jl",
   "mimetype": "application/julia",
   "name": "julia",
   "version": "1.0.1"
  }
 },
 "nbformat": 4,
 "nbformat_minor": 2
}
