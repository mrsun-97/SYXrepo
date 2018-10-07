{
 "cells": [
  {
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    " ### 数据处理 1"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": 10,
   "metadata": {},
   "outputs": [
    {
     "name": "stdout",
     "output_type": "stream",
     "text": [
      "Done!\n",
      "1600\n",
      "1502\n",
      "0.706 0.86549026 9.974375234521576e-5\n",
      "Done!\n"
     ]
    },
    {
     "data": {
      "text/plain": [
       "32000"
      ]
     },
     "execution_count": 10,
     "metadata": {},
     "output_type": "execute_result"
    }
   ],
   "source": [
    "using DelimitedFiles\n",
    "arr = readdlm(\"less.txt\", '\\t')\n",
    "println(\"Done!\")\n",
    "m = size(arr,1) #\n",
    "n = size(arr,2) #\n",
    "#println(arr[1:2,1:5])\n",
    "println(m,'\\n',n)\n",
    "λ_min = arr[1,1]\n",
    "λ_max = arr[end,1]\n",
    "ll = (λ_max - λ_min) / (m - 1.0)\n",
    "global i = 6\n",
    "println(λ_min,\" \",λ_max,\" \",ll)\n",
    "\n",
    "art = readdlm(\"Lyapunov.txt\", '\\t')\n",
    "println(\"Done!\")\n",
    "len = size(art,1)\n",
    "#println(len)\n"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "scrolled": false
   },
   "outputs": [],
   "source": [
    "using PyPlot\n",
    "fig = figure(figsize=[10, 8])\n",
    "grid(\"on\")\n",
    "#xticks(0.8652:0.00005:0.86559)\n",
    "#yticks(0.49:0.01:0.51)\n",
    "xlabel(\"λ\")\n",
    "xlim(0.7,0.8656)\n",
    "#ylim(0.494, 0.51)\n",
    "#ylabel(\"final x\")\n",
    "\n",
    "set = Array{Tuple{Float64,Float64},1}()\n",
    "set2 = copy(set)\n",
    "A = ones(3)\n",
    "\n",
    "for i = 2:m\n",
    "    B = A\n",
    "    A = ones(0)\n",
    "    for j = 2:(n-1)\n",
    "        tmp = arr[i,j]\n",
    "        if (tmp in A) == false #&& (0.49 <= tmp <= 0.515)\n",
    "            push!(A, tmp)\n",
    "        end\n",
    "    end\n",
    "    scatter((ones(length(A))*arr[i,1]),+A,s=0.5)\n",
    "    if length(A) != length(B)\n",
    "        push!(set, (arr[i-1,1], maximum(B)))\n",
    "        push!(set2, (arr[i,1],length(A)))\n",
    "    end\n",
    "end\n",
    "#println(set)\n",
    "\n",
    "for (λ, χ) in set\n",
    "    arrow(λ,\n",
    "    χ+0.05,\n",
    "    0.0,\n",
    "    -0.04,\n",
    "    head_width=0.002,\n",
    "    width=0.003,\n",
    "    #head_length=autoscale,\n",
    "    #overhang=0.5,\n",
    "    #head_starts_at_zero=\"true\",\n",
    "    length_includes_head=\"true\",\n",
    "    facecolor=\"red\")\n",
    "end\n",
    "scatter(art[:,1],art[:,2] .+ 0.5, s=0.5)\n",
    "#savefig(\"./prcs2.pdf\")"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": 13,
   "metadata": {},
   "outputs": [],
   "source": [
    "savefig(\"./fig1.pdf\")"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": 12,
   "metadata": {},
   "outputs": [
    {
     "name": "stdout",
     "output_type": "stream",
     "text": [
      "[0.122359, 4.4549, 4.72223, 4.50002]\n",
      "Tuple{Float64,Float64}[(0.7061, 1.0), (0.719964, 2.0), (0.833273, 4.0), (0.858708, 8.0), (0.864094, 16.0), (0.865291, 32.0)]\n"
     ]
    }
   ],
   "source": [
    "Δ = Array{Float64,1}()\n",
    "for k in 2:(length(set)-1)\n",
    "    push!(Δ, (set[k-1][1]-set[k][1])/(set[k][1]-set[k+1][1]))\n",
    "end\n",
    "println(Δ)\n",
    "println(set2)"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": 145,
   "metadata": {},
   "outputs": [
    {
     "name": "stdout",
     "output_type": "stream",
     "text": [
      "Done!\n",
      "20480\n"
     ]
    }
   ],
   "source": [
    "using PyPlot\n",
    "fig2= figure(figsize=[12,6])\n",
    "grid(\"on\")\n",
    "xticks(0.5:0.25:1.0)\n",
    "yticks(-0.1:0.05:0.1)\n",
    "scatter(art[:,1],art[:,2],s=1)"
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
   "version": "1.0.0"
  }
 },
 "nbformat": 4,
 "nbformat_minor": 2
}
