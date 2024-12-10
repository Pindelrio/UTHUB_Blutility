
# Herramientas en Unreal Engine 5.4 - Ejercicios

## Descripción General
Este proyecto contiene dos ejercicios desarrollados como parte de la asignatura "Herramientas" del máster en Unreal Engine. Ambos ejercicios están implementados en C++ y hacen uso de Blueprints para extender las funcionalidades del motor.

---

## Ejercicio 1: Librería de Blueprint para Listado de Dependencias

### Objetivo
Crear una librería de Blueprint en C++ que liste todos los **assets** del proyecto que tienen dependencias y exportar esta información en formato de árbol jerárquico a un archivo de log.

### Especificaciones
1. **Formato del Log**: 
   ```
   AssetRoot [ROOT]
   |- Dependency
   |- Dependency
      |- SubDependency
   ```
   - `AssetRoot`: Cualquier asset que no esté referenciado.
   - Ignorar los assets sin dependencias ni referencias.

2. **Comportamiento**:
   - La función debe ejecutarse automáticamente al arrancar el editor (Running Blueprints at Editor Startup).
   - Exportar el listado a `Saved/Logs/RefLogOutput_<date>.log` (Ejemplo: `RefLogOutput_20231017.log`).
   - Mostrar una ventana de confirmación (FMessageDialog) indicando que el proceso se completó.

3. **Ubicación del Log**:
   - Carpeta: `Saved/Logs`.

---

## Ejercicio 2: Blutility para Static Meshes

### Objetivo
Desarrollar una Blutility que permita identificar y exportar **Static Meshes** en el nivel actual que cumplan con ciertos criterios.

### Especificaciones
1. **Criterios de Selección**:
   - **Tris superiores a 10k**.
   - **Más de 5 slots de materiales**.
   - **Dimensiones absolutas mayores a 6000 unidades**.

2. **Exportación**:
   - Los Static Meshes seleccionados deben exportarse a la carpeta: `Saved/Rework`.

3. **JSON Opcional**:
   - Generar un archivo JSON con la información de los problemas detectados para cada Static Mesh. Ejemplo de formato:
     ```json
     {
       "StaticMesh_00": {
         "bHasManyTri": true,
         "bHasManyMats": false,
         "bIsMassive": true
       }
     }
     ```

---

## Configuración y Uso

### Ejercicio 1:
1. Compilar y abrir el proyecto en Unreal Engine.
2. Al arrancar el editor, se ejecutará automáticamente la función que genera el listado de dependencias.
3. Verifica el archivo de salida en `Saved/Logs`.
4. La ventana de confirmación (FMessageDialog) indicará si el proceso fue exitoso.

### Ejercicio 2:
1. Accede al nivel que deseas analizar.
2. Ejecuta la Blutility desde el editor para generar el listado.
3. Los Static Meshes seleccionados se exportarán a `Saved/Rework`.
4. Si se habilita la opción JSON, verifica los resultados en un archivo con los detalles de cada Static Mesh.

---

## Requisitos
- Unreal Engine 5.4.
- Conocimientos básicos de C++ y Blueprints.
- Familiaridad con la estructura de carpetas de proyectos en Unreal Engine.

---

## Observaciones
- Asegúrate de que el proyecto tenga permisos de escritura para las carpetas `Saved/Logs` y `Saved/Rework`.
- La generación del JSON es opcional, pero altamente recomendable para identificar rápidamente los problemas.

