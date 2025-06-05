# **Hands On Lab: Gestió de Processos**
*Autors: Zakaria Hamdaoui, Joel Martínez Arjona, Sofía Giner Vargas*

## 1. Mesurar el temps

### **Frames per segon amb 1 rectangle**
**Processador:** [Especifica el teu processador]
**FPS obtinguts:** [X] fps amb MAXR=1

### **Increment de MAXR fins obtenir <10 FPS**

| **MAXR** | **FPS** | **Observacions** |
|:--------:|:-------:|:----------------:|
| 1        | XXX     | Molt ràpid       |
| 10       | XXX     | Encara ràpid     |
| 100      | XXX     | Comença a baixar |
| 500      | XXX     | Notem la baixada |
| 1000     | < 10    | Objectiu assolit |

## 2. Execució en paral·lel

### **Comparació de rendiment per threads**

| **Threads** | **FPS** | **Millora** | **Eficiència** |
|:-----------:|:-------:|:-----------:|:--------------:|
| 1 (original)| XXX     | -           | 100%           |
| 2           | XXX     | +X%         | X%             |
| 4           | XXX     | +X%         | X%             |
| 8           | XXX     | +X%         | X%             |
| 16          | XXX     | +X%         | X%             |
| 32          | XXX     | +X%         | X%             |

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
| 2           | 20M        | XXX      | XXX       | X%           |
| 4           | 40M        | XXX      | XXX       | X%           |
| 8           | 80M        | XXX      | XXX       | X%           |

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