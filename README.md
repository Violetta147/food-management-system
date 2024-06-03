# PBL1

Food management system

## Quick run

```bash
./run.sh

# Or
bash run.sh
```

## Note

header should include `#pragma once`

```mermaid
stateDiagram
A[Start] --> B[Input (X to exit)]
B --> C[Enter mode (A/C)]
C --> D[mode == 'A']
D --> E[Administrator mode]
E --> F[Password check (conf)]
F --> G[Read menu (Food.txt)]
G --> H[Print admin menu (printMenuAdmin)]
H --> I[User input (Ans)]
I --> J[move == 'D' (erase)]
J --> G
I --> K[move == 'A' (extend)]
K --> G
I --> L[move == 'C' (custom)]
L --> G
I --> M[move == 'S' (Statistics)]
M --> G
C --> N[mode == 'C']
N --> O[Customer mode (Customer)]
O --> B
B --> P[Exit program]
```
