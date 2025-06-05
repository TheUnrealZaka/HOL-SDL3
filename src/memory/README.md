# **Hands On Lab: Memòria**
*Autors: Zakaria Hamdaoui, Sofía Giner Vargas i Joel Martínez Arjona*

## 1. Avaluant matrius...

### **Fes una taula amb les mides de la matriu i els temps d'execució pels dos recorreguts**

#### **Matriu de 64x64**
| **Execució** | **Inicialització (µs)** | **Fila (µs)** | **Mitjana Fila (µs)** | **Columna (µs)** | **Mitjana Columna (µs)** |
|:------------:|:----------------------:|:-------------:|:---------------------:|:----------------:|:------------------------:|
| 1 | 6 | 10, 6, 7 | 7.67 | 8, 12, 12 | 10.67 |
| 2 | 7 | 7, 10, 10 | 9.00 | 6, 11, 6 | 7.67 |
| 3 | 5 | 10, 10, 5 | 8.33 | 11, 11, 6 | 9.33 |
| 4 | 10 | 10, 9, 6 | 8.33 | 11, 11, 11 | 11.00 |
| 5 | 10 | 10, 5, 5 | 6.67 | 6, 11, 6 | 7.67 |

#### **Matriu de 128x128**
| **Execució** | **Inicialització (µs)** | **Fila (µs)** | **Mitjana Fila (µs)** | **Columna (µs)** | **Mitjana Columna (µs)** |
|:------------:|:----------------------:|:-------------:|:---------------------:|:----------------:|:------------------------:|
| 1 | 35 | 35, 40, 37 | 37.33 | 29, 28, 29 | 28.67 |
| 2 | 37 | 37, 40, 37 | 38.00 | 28, 28, 28 | 28.00 |
| 3 | 32 | 37, 39, 40 | 38.67 | 37, 28, 29 | 31.33 |
| 4 | 37 | 37, 41, 37 | 38.33 | 45, 28, 46 | 39.67 |
| 5 | 37 | 40, 43, 38 | 40.33 | 28, 30, 28 | 28.67 |

#### **Matriu de 256x256**
| **Execució** | **Inicialització (µs)** | **Fila (µs)** | **Mitjana Fila (µs)** | **Columna (µs)** | **Mitjana Columna (µs)** |
|:------------:|:----------------------:|:-------------:|:---------------------:|:----------------:|:------------------------:|
| 1 | 134 | 129, 128, 123 | 126.67 | 165, 162, 165 | 164.00 |
| 2 | 154 | 140, 144, 138 | 140.67 | 192, 188, 185 | 188.33 |
| 3 | 166 | 150, 138, 140 | 142.67 | 176, 175, 187 | 179.33 |
| 4 | 139 | 139, 133, 146 | 139.33 | 172, 178, 175 | 175.00 |
| 5 | 141 | 134, 144, 140 | 139.33 | 183, 172, 182 | 179.00 |

#### **Matriu de 512x512**
| **Execució** | **Inicialització (µs)** | **Fila (µs)** | **Mitjana Fila (µs)** | **Columna (µs)** | **Mitjana Columna (µs)** |
|:------------:|:----------------------:|:-------------:|:---------------------:|:----------------:|:------------------------:|
| 1 | 453 | 455, 453, 451 | 453.00 | 713, 710, 694 | 705.67 |
| 2 | 472 | 481, 541, 625 | 549.00 | 774, 745, 746 | 755.00 |
| 3 | 498 | 482, 489, 490 | 487.00 | 758, 753, 781 | 764.00 |
| 4 | 492 | 519, 489, 549 | 519.00 | 788, 781, 762 | 777.00 |
| 5 | 512 | 507, 531, 513 | 517.00 | 803, 803, 770 | 792.00 |

#### **Matriu de 1024x1024**
| **Execució** | **Inicialització (µs)** | **Fila (µs)** | **Mitjana Fila (µs)** | **Columna (µs)** | **Mitjana Columna (µs)** |
|:------------:|:----------------------:|:-------------:|:---------------------:|:----------------:|:------------------------:|
| 1 | 1797 | 1988, 1923, 1963 | 1958.00 | 4279, 3702, 3306 | 3762.33 |
| 2 | 1831 | 1872, 1922, 1980 | 1924.67 | 4566, 4139, 3618 | 4107.67 |
| 3 | 2042 | 2231, 1893, 1940 | 2021.33 | 3737, 4246, 4041 | 4008.00 |
| 4 | 2017 | 2012, 1879, 1887 | 1926.00 | 3792, 3675, 2941 | 3469.33 |
| 5 | 1729 | 1798, 1698, 1685 | 1727.00 | 3611, 3427, 4929 | 3989.00 |

#### **Matriu de 2048x2048**
| **Execució** | **Inicialització (µs)** | **Fila (µs)** | **Mitjana Fila (µs)** | **Columna (µs)** | **Mitjana Columna (µs)** |
|:------------:|:----------------------:|:-------------:|:---------------------:|:----------------:|:------------------------:|
| 1 | 5165 | 5368, 5472, 5361 | 5400.33 | 33512, 33177, 29950 | 32213.00 |
| 2 | 4813 | 5446, 5266, 5088 | 5266.67 | 30354, 31300, 31798 | 31150.67 |
| 3 | 5299 | 5046, 5232, 5329 | 5202.33 | 31961, 29804, 31604 | 31123.00 |
| 4 | 5423 | 5423, 5154, 5094 | 5223.67 | 32285, 30948, 29276 | 30836.33 |
| 5 | 5549 | 5325, 5435, 5262 | 5340.67 | 31884, 31367, 32021 | 31757.33 |

#### **Matriu de 4096x4096**
| **Execució** | **Inicialització (µs)** | **Fila (µs)** | **Mitjana Fila (µs)** | **Columna (µs)** | **Mitjana Columna (µs)** |
|:------------:|:----------------------:|:-------------:|:---------------------:|:----------------:|:------------------------:|
| 1 | 27660 | 29334, 27476, 25440 | 27416.67 | 202253, 210451, 200421 | 204375.00 |
| 2 | 26408 | 24724, 23795, 26100 | 24873.00 | 206816, 191936, 206150 | 201634.00 |
| 3 | 25076 | 26301, 24732, 29378 | 26803.67 | 243667, 248421, 231174 | 241087.33 |
| 4 | 24548 | 23268, 24413, 25418 | 24366.33 | 202175, 205512, 204223 | 203970.00 |
| 5 | 25296 | 25754, 28058, 27581 | 27131.00 | 226349, 216389, 215395 | 219377.67 |

### **Anàlisi dels Resultats**

#### **És similar el temps d'execució quan es recorre per files i per columnes?**
**No.** Inicialment, en matrius petites (64x64, 128x128), els temps són relativament similars. Però a mesura que la dimensió de la matriu augmenta, el temps d'execució per columnes esdevé **significativament superior** al de files.

**Ràtios de degradació:**
- **512x512**: ~1.5x més lent per columnes
- **1024x1024**: ~2x més lent per columnes  
- **4096x4096**: ~8x més lent per columnes

#### **Anàlisi tècnica**

**Mida d'una fila en matriu 512x512:**
- 512 elements × 1 byte/element = **512 bytes**

**Explicació de la diferència de rendiment:**

Aquest canvi és degut a la **localitat espacial** i el funcionament de la memòria cache:

1. **Recorregut per files:** Els elements són consecutius en memòria → alta localitat espacial → molts **cache hits**
2. **Recorregut per columnes:** Salts de 512 bytes entre accessos → baixa localitat espacial → molts **cache misses**

#### **Relació amb la jerarquia de memòria**

**Cache del processador utilitzat:**
- **L1 Data Cache:** 8×48 KB = 384 KB total  
- **L2 Cache:** 8×1.25 MB = 10 MB total
- **L3 Cache:** 24 MB

**Impacte per mida de matriu:**
- **64×64 (4 KB):** Cap completament a L1 → temps similars
- **256×256 (64 KB):** Comença a superar L1 → lleuger impacte
- **512×512 (256 KB):** Supera L1, usa L2 → diferència notable
- **2048×2048 (4 MB):** Supera L2, usa L3 → gran diferència
- **4096×4096 (16 MB):** Supera L2, usa parcialment L3 → màxima diferència

---

## 2. Patrons d'accés i impacte de la cache

### **Versió seleccionada: JKI**

```c
for (j=0; j<N; j++)        // bucle exterior
  for (k=0; k<N; k++)      // bucle mitjà  
    for (i=0; i<N; i++)    // bucle interior
      C[i][j] = C[i][j] + A[i][k] * B[k][j];
```

### **Temps d'execució**

| **Dimensió (N)** | **Temps (ms)** |
|:-----------------:|:--------------:|
| 256 | 57.778 |
| 512 | 849.848 |
| 1024 | 9683.562 |

### **Patró d'accés a les matrius**

Per cada execució completa del **bucle interior (i)**:

- **Matriu A:** `A[0][k], A[1][k], ..., A[N-1][k]` → accés per **columna**
- **Matriu B:** `B[k][j]` → **1 element constant**
- **Matriu C:** `C[0][j], C[1][j], ..., C[N-1][j]` → accés per **columna**

### **Càlcul de pàgines de memòria virtual**

**Paràmetres:**
- Element: 4 bytes (float)
- Pàgina: 4096 bytes
- Elements per pàgina: 4096 ÷ 4 = **1024 elements**

**Càlculs per matriu:**

#### **Matriu A (accés per columna)**
Elements per columna = N  
Pàgines = ⌈N ÷ 1024⌉

#### **Matriu B (1 element)**  
Pàgines = 1

#### **Matriu C (accés per columna)**
Elements per columna = N  
Pàgines = ⌈N ÷ 1024⌉

### **Resultats**

| **N** | **Matriu A** | **Matriu B** | **Matriu C** |
|:-----:|:------------:|:------------:|:------------:|
| 256 | 1 | 1 | 1 |
| 512 | 1 | 1 | 1 |
| 1024 | 1 | 1 | 1 |
| 2048 | 2 | 1 | 2 |

> **Nota:** L'accés per columnes és ineficient perquè cada element accedeix a una pàgina diferent, provocant molts cache misses.

---

## 3. Memòria dinàmica

### **Motxilla del bruixot**

✅ **Implementació completada a `geraldBag.c`**

El programa implementa:
- **Estructura:** Llista encadenada d'elements
- **Funcionalitats:**
  - Afegir nous elements
  - Llistar elements existents  
  - Gestió automàtica de memòria
- **Compatibilitat:** Windows i Linux

### **Limitacions [Opcional]**

#### **Anàlisi de `mem.c`**

**Comportament observat:**
1. **Accessos legals (0-9):** Escrits dins del rang de `malloc(10)` → ✅ Funciona
2. **Accessos il·legals (10-19):** Escrits fora del rang reservat → ⚠️ Funciona (per ara)
3. **Accessos extrems (20+):** → ❌ Segmentation fault

**Explicació tècnica:**
- El sistema operatiu assigna memòria en **pàgines de 4096 bytes**
- `malloc(10)` pot estar dins d'una pàgina més gran
- Els accessos il·legals inicials poden caure dins de la mateixa pàgina → aparentment "legals"
- Quan s'arriba als límits de la pàgina → el SO detecta l'accés il·legal

#### **Anàlisi de `mem2.c`**

**Seqüència d'events:**
1. **X reservada** amb `malloc(10)` → escriptura legal
2. **X alliberada** amb `free(x)`
3. **Y reservada** amb `malloc(10)` → escriptura inicial legal
4. **Corrupció massiva:** Escriptura fins a posició 133000
5. **Intent de `free(y)`** → ❌ Heap completament corromput

**Conseqüències de la corrupció:**
- **Metadades del heap** destruïdes
- **free()** no pot funcionar correctament
- **Futurs malloc()** poden fallar
- **Comportament impredictible** del programa

> **⚠️ Lliçó:** Mai accedir a memòria fora dels límits reservats, encara que sembli "funcionar"

---

## 4. Conclusions

1. **Cache és crucial:** La localitat espacial determina el rendiment
2. **Patrons d'accés importants:** Files vs columnes pot ser 8x diferència
3. **Gestió de memòria:** Respectar sempre els límits de `malloc()`
4. **Debugging:** Les violacions de memòria poden ser silencioses inicialment