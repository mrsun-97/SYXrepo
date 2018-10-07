{
 "cells": [
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": [
    "using PyPlot\n",
    "using DelimitedFiles\n",
    "\n",
    "arr = readdlm(\"data.txt\", '\\t')\n",
    "Len = arr[1,1]\n",
    "Hei = arr[1,2]\n",
    "arr = arr[2:end,:]\n",
    "art = arr'\n",
    "println(Len,\"\\t\",Hei,\"\\tDone!\")"
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
    "fig = figure(figsize=[10, 10])\n",
    "grid(\"on\")\n",
    "xlabel(\"x\")\n",
    "xlim(200,800)\n",
    "#xlim(0,Len)\n",
    "#xticks(0:Len/5:Len)\n",
    "ylabel(\"y\")\n",
    "ylim(200,800)\n",
    "#ylim(0,Hei)\n",
    "#yticks(0:Hei/5:Hei)\n",
    "scatter(art[1,:], art[2,:],s=1.5)\n",
    "name = \"[336]\"\n",
    "c = \"1\"\n",
    "savefig(\"./$name$c.jpg\")\n",
    "f = open(\"./$name$c.dat\", \"w\")\n",
    "for i = 1:size(arr,1)\n",
    "    writedlm(f,[arr[i,1] arr[i,2]])\n",
    "end\n",
    "a = b = 0\n",
    "close(f)"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": [
    "ars = readdlm(\"[336]1.dat\", '\\t')\n",
    "fig = figure(figsize=[10, 10])\n",
    "grid(\"on\")\n",
    "xlabel(\"x\")\n",
    "xlim(200,800)\n",
    "#xlim(0,Len)\n",
    "#xticks(0:Len/5:Len)\n",
    "ylabel(\"y\")\n",
    "ylim(200,800)\n",
    "#ylim(0,Hei)\n",
    "#yticks(0:Hei/5:Hei)\n",
    "scatter(ars'[1,:], ars'[2,:],s=2)\n",
    "savefig(\"[338]x.jpg\")"
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
