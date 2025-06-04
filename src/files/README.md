## Heads on Lab - Gestió d'entrada/sortida
### Autors: Zakaria Hamdaoui, Joel Martínez Arjona i Sofia Giner Vargas

### 1. Paths per MYSTRING.TXT

**Path absolut:**
```
C:\Users\Zakaria\Documents\GitHub\HOL\MYSTRING.TXT
```

**Path relatiu:**
```
.\MYSTRING.TXT
```
o simplement:
```
MYSTRING.TXT
```

### 2. Contingut de MYSTRING.TXT quan l'obro amb Notepad

Quan obro el fitxer MYSTRING.TXT amb el Notepad, veig exactament el text que vaig introduir quan vaig executar write_string.c. Per exemple, si vaig escriure "Hello world", veig:
```
Hello world
```

### 3. Contingut de MYINTS.TXT quan l'obro amb Notepad

Quan obro el fitxer MYINTS.TXT amb el Notepad, **NO** veig els números que vaig introduir. En lloc d'això, veig caràcters estranys i símbols raros.

Així que veig quelcom com:
```
HOLA[caràcters estranys]HELLO
```

### 4. Hall of Fame - Gestió de dades mixtes

El nostre hall_of_fame.c resol elegantment el problema de guardar dades de tipus diferents:

- Fem servir una `struct Player` amb mida fixa (50 chars + 1 int)
- Això ens permet llegir/escriure fàcilment amb `SDL_ReadIO`/`SDL_WriteIO`
- Evitem la complexitat de guardar primer la mida de la cadena