import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

#load data
logSummary = pd.read_csv("logSummary.-144.dat", sep='\t')
P = logSummary.p
V = logSummary.v
CA = np.array(logSummary.CA)
NOX = logSummary.NOX
Ysoot = logSummary.Soot

HoleNum = 7
#CA = CA - 720
P  = P/1E+06

for i in range(0,len(logSummary)-1):
    if CA[i] == -70:   indc2=i
    if CA[i] == 115:   indc3=i
    if CA[i] == -14.0:   indc4=i
print(indc2)
print(indc3)
# Find displacement volume
Vmax = max(V)
Vmin = min(V)
Vdis = Vmax - Vmin
print("Vmax = ",Vmax,"m3")
print("Vmin = ",Vmin,"m3")
print("Vdis = ",Vdis,"m3")
#Vdis = Vdis*7
print("VDIS =", Vdis)
#calculate mean of pressure and dv to find the area of the curve
PP = [(P[i+1]+P[i])/2. for i in range(len(logSummary)-1)]
dV = [abs(V[i+1]-V[i]) for i in range(len(logSummary)-1)]
# calculate pdv from IVC to TDC (np.argmax(P))
te1 = [PP[i]*dV[i] for i in range(indc2,np.argmax(P))]
# calculate pdv from TDC to EVO
te2 = [PP[i]*dV[ i] for i in range(np.argmax(P),indc3)]
# find the area between two curves
ANS = abs(sum(te2)-sum(te1))
print(sum(te1)/Vdis*10)
print(sum(te2)/Vdis*10)
# calculate indicated mean pressure in bar
#Vdis = 0.00026442999999999996
IMEP = ANS / Vdis *10
#IMEP = 13.09
# calculate indicated power
n = 2000 / 60   #round per secconds
ncycle = n/2            #n/2 for four stroke engine
Power = IMEP * 1E+2 * Vdis * ncycle * HoleNum * 6
# calculate indicated torque
IT = (IMEP * 1E+5 * Vdis * HoleNum * 6) / (4.* np.pi)
# calculate indicated fuel consumption
mcf = 2.1714286 * 1E-02 * 1E-03 * HoleNum * 6 #total mass of fuel trapped in cylinder
ISFC = (mcf * ncycle * 3600) / Power

# mean Ysoot and NOX
MeanNOX   = sum(NOX)/(len(logSummary)-1-indc4)
MeanYsoot = sum(Ysoot)/(len(logSummary)-1-indc4)

#conver meanNOX to ppm and g/kwh
AFR = 34.95
FuelFlow = ISFC * Power  #Fuel Flow (kg/hr)
AirFlow = AFR * FuelFlow
ExhaustFlow = AirFlow + FuelFlow
StandardMeanNOX = 0.001587 * max(NOX) * 1E+06 * ExhaustFlow / Power #gm/kWhr
StandardMeanNOX2 = 6.636E-03 * MeanNOX  * 1E+06

#print data
print("Compression Ratio",Vmax/Vmin)
print("IMEP = ",IMEP,"bar")
print("Indicated Power = ",Power,"kW")
print("Indicated Torque = ",IT,"N.m")
print("ISFC = ",ISFC)
print("MeanNOX = ",MeanNOX)
print("StandardMeanNOX = ",StandardMeanNOX)
print("MeanYsoot = ",MeanYsoot)
plt.plot(V, P)
#plt.plot(CA, P)