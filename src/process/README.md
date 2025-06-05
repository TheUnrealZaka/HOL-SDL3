# **Hands On Lab: Gestió de Processos**
*Autors: Zakaria Hamdaoui, Joel Martínez Arjona, Sofía Giner Vargas*

## 1. Mesurar el temps

### **Frames per segon amb 1 rectangle**
**Processador:** Intel Core i5 13600 KF
**FPS obtinguts:** 3960 fps amb MAXR=1

### **Increment de MAXR fins obtenir <10 FPS**

| **MAXR** | **FPS** | **Observacions** |
|:--------:|:-------:|:----------------:|
| 1        | 3960     | Molt ràpid      |
| 10       | 3960     | Molt ràpid      |
| 100      | 3960     | Molt ràpid |
| 500      | 3960     | Molt ràpid |
| 1000     | 3900    | Ràpid |
| 10000     | 500    | Baixa bastant |
| 15000     | 340    | Baixa progressivament |
| 25000     | 200    | Baixa progressivament |
| 50000     | 102    | Baixa progressivament |
| 100000     | 51    | Baixa notoriament |
| 200000     | 23    | Baixa notoriament |
| 300000     | 18    | Baixa notoriament |
| 400000     | 12    | Li costa baixar |
| 500000     | 11    | Li costa baixar |
| 550000     | 9    | Objectiu assolit |




## 2. Execució en paral·lel

### **Comparació de rendiment per threads**

| **Threads** | **FPS** | **Millora** | **Eficiència** |
|:-----------:|:-------:|:-----------:|:--------------:|
| 1 (original)| 3960     | -           | 100%           |
| 2           | 56     | +X%         | X%             |
| 4           | 55    | +X%         | X%             |
| 8           | 57     | +X%         | X%             |
| 14          | 56     | +X%         | X%             |


### **Conclusions**
- **Millor rendiment:** X threads
- **Punt de saturació:** X threads
- **Raó:** [Explicar per què no millora linealment]

## 3. Compartint recursos

### **Shared increment - Teòric vs Real**

#### **Valors teòrics esperats:**
- **1 thread:** 10,000,000
- **2 threads:** 20,000,000  
- **4 threads:** 40,000,000
- **8 threads:** 80,000,000

#### **Valors reals obtinguts:**

| **Threads** | **Teòric** | **Real** | **Error** | **% Perdut** |
|:-----------:|:----------:|:--------:|:---------:|:------------:|
| 1           | 10M        | 10M      | 0         | 0%           |
| 2           | 20M        | 1114765     | 885235       | 44.26%           |
| 4           | 40M        | 1773252      | 2226748       | 55.67%           |
| 8           | 80M        | 1424110      | 6575890       | 82.20%           |
| 14           | 140M        | 1787806      | 12212194       | 87.23%           |

#### **Anàlisi race conditions:**
- **Problema:** Condicions de carrera (race conditions)
- **Causa:** Accés concurrent a variable global sense protecció
- **Solució:** Mutex per exclusió mútua

### **Resultats amb mutex (shared_inc_safe):**
✅ **Tots els valors coincideixen amb la teoria**

## 4. Conclusions

1. **Threads milloren el rendiment** fins a un punt de saturació
2. **Race conditions** són un problema real en programació concurrent  
3. **Mutex** resol la compartició segura de recursos
4. **Cost de sincronització** pot reduir els beneficis del paral·lelisme