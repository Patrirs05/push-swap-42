
1. Bloque de Preprocesamiento (Indexación)

Este bloque se ejecuta una sola vez al principio, antes de empezar a mover los stacks.
• void bubble_sort_array(int *arr, int size)
	• Qué hace: Ordena un array temporal de enteros (puede ser un Bubble Sort simple o un QuickSort, da igual porque no afecta al límite de movimientos de Push Swap).
• void index_stack_a(t_stack *stack_a, int size)
	• Qué hace: Pide memoria para el array temporal, copia los valores actuales de A, llama a la función de ordenar, y luego recorre tu Stack A reemplazando cada value original por su posición (index) en el array ordenado. Libera el array al terminar.

    1. Copias los valores reales a un array: Si tu stack tiene los valores [42, -5, 12], tu array recién creado con malloc tendrá exactamente [42, -5, 12].
    2. Ordenas ese array: Llamas a tu función bubble_sort_array. Ahora tu array en memoria cambia a [-5, 12, 42].
    3. Miras las posiciones (índices) del array:
        • El número -5 está en la posición 0.
        • El número 12 está en la posición 1.
        • El número 42 está en la posición 2.
    4. Asignas el índice directamente a los nodos de la lista: Recorres tu lista original. Cuando el código ve el nodo con el valor 42, busca en el array, ve que el 42 está en la posición 2, y hace: nodo->index = 2;.
    Al final, el array se destruye con free. Lo único que sobrevive son los nodos de tu lista enlazada, que ahora tendrán su campo index relleno con el número correcto. El array solo ha sido una herramienta temporal para calcularlos.

2. Bloque de Control de Chunks (Fase A → B)

Estas funciones se encargan de vaciar el Stack A manteniendo la "ventana" o rango del chunk.
• int get_chunk_size(int size)
	• Qué hace: Una función simple que recibe el número total de elementos y devuelve el tamaño ideal del chunk (por ejemplo, si size == 100, devuelve 18 o 20). Te permite cambiar el tamaño del chunk en un solo sitio para hacer pruebas.

    Cuando el corrector te pregunte: ¿De dónde sale ese sqrt * 2?, tu respuesta científica será:
    1. La Base Teórica (\(O(n\sqrt{n})\)): "Por definición de complejidad algorítmica para ordenación por bloques, el equilibrio óptimo entre las rotaciones de búsqueda en A y el desorden generado en B se alcanza dividiendo el stack en la raíz cuadrada de sus elementos (\(\sqrt{n}\))."
    2. La Optimización del Doble Filtrado: "Sin embargo, mi función push_all_chunks no arroja los números en B de forma caótica. Aplica un filtrado de dos niveles: los elementos menores se quedan arriba de B y los mayores van al fondo mediante rb. Esto reduce el desorden real de B a la mitad."
    3. La Deducción del Multiplicador: "Como el coste de recuperar los elementos desde B se ha reducido a la mitad gracias a este diseño de 'cebolla', la balanza matemática me permite duplicar el tamaño del chunk (sqrt * 2). Esto reduce a la mitad las vueltas innecesarias en el Stack A sin penalizar la fase de retorno, logrando el mínimo absoluto de movimientos."

• void push_all_chunks(t_stack **stack_a, t_stack **stack_b)
	• Qué hace: El bucle principal de la primera fase. Controla el contador (count), obtiene el tamaño del chunk y corre un while (*stack_a) que va llamando a las operaciones de empuje y rotación.

    Vas a crear un bucle while que no parará hasta que el Stack A esté completamente vacío. En cada vuelta de ese bucle, tu programa mirará el índice (index) del número que está arriba del todo en A, y tendrá que tomar una de estas tres decisiones:

    🛑 Decisión 1: ¿El número es de la parte más baja del rango actual?

    • La condición: Compara si el índice del tope de A es menor o igual que tu variable count.
    • Qué significa: Significa que es uno de los números más pequeños del bloque que estás procesando ahora mismo.
    • Qué tienes que hacer:
        1. Lo mandas al Stack B usando tu función pb. (Se quedará arriba en B).
        2. Sumas 1 a tu variable count.

    🔽 Decisión 2: ¿El número pertenece al rango actual, pero es de la parte alta?

    • La condición: Si no se cumplió la anterior, comprueba si el índice del tope de A es menor que la suma de (count + chunk_size).
    • Qué significa: Significa que el número entra dentro del grupo actual que queremos enviar a B, pero es de los "grandes" de ese grupo.
    • Qué tienes que hacer:
        1. Lo mandas al Stack B usando tu función pb.
        2. Inmediatamente después, haces girar el Stack B usando tu función rb. Esto manda ese número al fondo de B, protegiendo a los más pequeños que se quedaron arriba.
        3. Sumas 1 a tu variable count.

    🔄 Decisión 3: ¿El número es demasiado grande para el grupo actual?

    • La condición: Si no cumple ninguna de las dos condiciones anteriores (el número pertenece a un chunk del futuro).
    • Qué significa: No queremos mover este número a B todavía porque descuadraría nuestro orden de capas.
    • Qué tienes que hacer:
        1. Haces girar el Stack A usando tu función ra. Esto manda el número al fondo de A para quitártelo de en medio y que en la siguiente vuelta del bucle aparezca un número nuevo en el tope.
        2. (Aquí NO sumas nada a count, porque no has enviado ningún número a B).

    ¿Por qué esta lógica es brillante? (Para tu defensa)

    Fíjate en lo que pasa con la condición 2: count + chunk_size.
    Como cada vez que haces un pb sumas 1 a count, el límite de tu ventana va subiendo de valor de forma automática. Los números grandes que al principio daban "falso" y se iban al fondo con ra, unas cuantas vueltas más tarde darán "verdadero" porque count habrá aumentado lo suficiente como para alcanzarlos.
    Cuando el bucle termine, el Stack A estará vacío y habrás creado esa estructura de "cebolla" en B de la que hablábamos.

3. Bloque de Búsqueda y Eficiencia (Fase B → A)

Para devolver los números a A de forma óptima, necesitas calcular distancias dentro del Stack B.
• int find_max_index_position(t_stack *stack_b)
	• Qué hace: Recorre el Stack B buscando cuál es el nodo que contiene el índice más alto actualmente y devuelve su posición física actual (por ejemplo: posición 0 si está arriba, posición 5 si está en medio).

    1. Variables que necesitas:
	• Un puntero auxiliar para recorrer la lista (aquí sí se usa, por ejemplo t_stack *curr = stack_b;).
	• Una variable para guardar el índice máximo encontrado (int max_idx = -1;).
	• Una variable para guardar la posición de ese máximo (int max_pos = 0;).
	• Un contador para saber en qué posición de la lista estás parado en cada vuelta (int current_pos = 0;).
    2. El bucle de búsqueda: Mientras curr no sea NULL:
        • Comparas: ¿El curr->index es mayor que tu max_idx?
        • Si es verdad: actualizas tu max_idx con ese nuevo valor y guardas la posición actual (max_pos = current_pos).
        • Avanzas al siguiente nodo (curr = curr->next) e incrementas tu contador de posición (current_pos++).
    3. El final: Cuando el bucle termine, devuelves max_pos.

• void bring_max_to_top(t_stack **stack_b, int max_pos)
	• Qué hace: Recibe la posición del número máximo y calcula el tamaño actual del Stack B. Decide qué es más rápido: si la posición está en la mitad superior, ejecuta rb en un bucle; si está en la mitad inferior, ejecuta rrb. Se detiene cuando el máximo está en la posición 0.

    📋 ¿Qué tiene que hacer esta función?

    1. Calcular el tamaño actual de B: Usa tu función stack_size(*stack_b).
    2. Tomar la decisión estratégica (La Mitad):
        • Caso A (Mitad Superior): Si max_pos es menor o igual que la mitad del tamaño del stack (size / 2), significa que el número está cerca del tope. El camino más corto es moverlo hacia arriba.
            • ¿Qué hacer? Un bucle que ejecute tu función rb(stack_b) tantas veces como sea necesario para que el número llegue arriba. (Pista: el bucle puede restar max_pos hasta llegar a 0).
        • Caso B (Mitad Inferior): Si max_pos es mayor que la mitad del tamaño, el número está cerca del fondo. El camino más corto es moverlo hacia abajo.
            • ¿Qué hacer? Un bucle que ejecute tu función rrb(stack_b). Aquí, la cantidad de movimientos necesarios será la diferencia entre el tamaño total del stack y la posición del elemento (size - max_pos).

• void return_to_a(t_stack **stack_a, t_stack **stack_b)
	• Qué hace: El bucle principal de la segunda fase. Mientras B tenga elementos: llama a find_max_index_position, luego a bring_max_to_top, y finalmente ejecuta pa.

    Esta función debe ejecutarse mientras el Stack B no esté vacío. En cada vuelta del bucle, tu código hará lo siguiente:
    1. Localizar al "Rey" actual de B: Llama a tu función find_max_index_position pasándole el Stack B real (*stack_b). Guarda ese resultado en una variable local (por ejemplo, int pos;).
    2. Llevarlo arriba: Llama a tu función bring_max_to_top pasándole la dirección de B y la posición que acabas de encontrar. Esta función se encargará de hacer todos los rb o rrb necesarios para dejar al número más grande del stack arriba del todo.
    3. Pasarlo a A: Una vez que el número máximo está en la pole position (posición 0), ejecutas tu función básica pa(stack_a, stack_b).
    Como siempre buscas el número más grande que quede en B, los números irán cayendo en A en orden descendente (el 99, luego el 98, luego el 97...). Al ir apilándose en A, el 99 terminará abajo del todo y los números pequeños irán quedando arriba. Cuando B se quede a cero, ¡el Stack A estará perfectamente ordenado de menor a mayor!

4. Función Principal del Algoritmo

La función que invocarás desde tu main.c cuando detectes que te han pasado, por ejemplo, más de 5 o 10 números.
• void sort_with_chunks(t_stack **stack_a, t_stack **stack_b)
	• Qué hace: Es la directora de orquesta. Llama a las funciones en estricto orden secuencial:
		1. index_stack_a(...)
		2. push_all_chunks(...)
        3. return_to_a(...)

        Para rematar el proyecto, necesitas la función "directora de orquesta" que llamarás desde tu main.c. Esta función simplemente invocará las fases que hemos construido en estricto orden secuencial:
        1. Llamas a index_stack_a (para transformar los valores reales en índices del 0 al N-1).
        2. Llamas a push_all_chunks (para vaciar A hacia B en forma de cebolla).
        3. Llamas a return_to_a (para devolver los números de B a A en perfecto orden).
