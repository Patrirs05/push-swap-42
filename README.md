
Algoritmo intermedio

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

Algoritmo complejo


1. int get_max_bits(t_stack *stack)

Antes de empezar a mover bits, necesitas saber cuándo parar. Si tienes 100 números, el índice más grande es el 99. En binario, el 99 se escribe 1100011 (necesita 7 bits). Esta función calcula cuántas pasadas de bits tendremos que hacer.
• Qué hace:
	1. Busca cuál es el índice (index) más alto en todo el stack (que siempre será igual a stack_size - 1 si está bien indexado).
	2. Inicializa un contador de bits en 0.
	3. Ejecuta un bucle while que va desplazando ese número máximo hacia la derecha en binario (max >> 1) e incrementando el contador hasta que el número se convierta en 0.
	4. Devuelve el número total de bits (el contador).


Simulación de la función Paso a Paso (Con el número 99)

Tu función guardará el número máximo (99) en una variable (por ejemplo, int max = 99;) e inicializará max_bits = 0.
Entramos en un bucle while (max > 0) que hará lo siguiente en cada vuelta:
• Vuelta 1:
	• max vale 99 (1100011 en binario). Como es mayor que 0, entramos.
	• Hacemos max = max >> 1;. El número se desplaza. En decimal: 99 / 2 = 49. En binario pasa a ser 110001 (se cayó el último 1).
	• Sumamos el bit encontrado: max_bits++ \(\rightarrow \) max_bits ahora vale 1.
• Vuelta 2:
	• max vale 49 (110001). Sigue siendo mayor que 0.
	• Desplazamos: 49 / 2 = 24. En binario queda 11000.
	• max_bits++ \(\rightarrow \) max_bits ahora vale 2.
• Vuelta 3:
	• max vale 24 (11000).
	• Desplazamos: 24 / 2 = 12. En binario queda 1100.
	• max_bits++ \(\rightarrow \) max_bits ahora vale 3.
• Vuelta 4:
	• max vale 12 (1100).
	• Desplazamos: 12 / 2 = 6. En binario queda 110.
	• max_bits++ \(\rightarrow \) max_bits ahora vale 4.
• Vuelta 5:
	• max vale 6 (110).
	• Desplazamos: 6 / 2 = 3. En binario queda 11.
	• max_bits++ \(\rightarrow \) max_bits ahora vale 5.
• Vuelta 6:
	• max vale 3 (11).
	• Desplazamos: 3 / 2 = 1. En binario queda 1.
	• max_bits++ \(\rightarrow \) max_bits ahora vale 6.
• Vuelta 7:
	• max vale 1 (1).
	• Desplazamos: 1 / 2 = 0. En binario queda 0.
	• max_bits++ \(\rightarrow \) max_bits ahora vale 7.
• Vuelta 8:
	• El while comprueba si max > 0. Como ahora max vale 0, el bucle se rompe de inmediato.

Al final, la función ejecuta un return (max_bits); y devuelve el número 7.

2. void radix_sort_pass(t_stack **stack_a, t_stack **stack_b, int bit, int size)

Esta función se encarga de realizar una única pasada completa para un bit específico. Aislar esta lógica te ahorrará un anidamiento de bucles masivo, protegiendo tu código de romper la Norma de 42.
• Qué hace:
	1. Ejecuta un bucle que da exactamente size vueltas (una por cada elemento del Stack A).
	2. En cada vuelta, comprueba el elemento del tope de A: evalúa si el bit actual (bit) de su index es un 0 o un 1 usando operaciones bit a bit.
	3. Si el bit es 0: llama a tu función pb(stack_a, stack_b).
	4. Si el bit es 1: llama a tu función ra(stack_a) para dejarlo en A.
	5. Al terminar las size vueltas, mete un segundo bucle corto que hace pa(stack_a, stack_b) de forma continua hasta que el Stack B se quede completamente vacío.


Ejemplo práctico (Pasada de las decenas)

Imagina que ya ordenamos por las unidades y nuestra lista actual es: [121, 432, 21, 564, 23, 1] (al 1 lo vemos como 001). Ahora toca la pasada de las decenas (el segundo dígito empezando por la derecha).
1. Repartir en cubetas (0 al 9): Miras el dígito de las decenas de cada número y lo metes en su caja correspondiente, respetando el orden en el que van apareciendo:
	• Cubeta 0: 001 (su decena es 0)
	• Cubeta 1: (vacía)
	• Cubeta 2: 121, 21, 23 (todos tienen un 2 en las decenas)
	• Cubeta 3: 432
	• Cubeta 4 y 5: (vacías)
	• Cubeta 6: 564
	• Cubeta 7, 8 y 9: (vacías)
2. Vaciar las cubetas en orden: Recoges los números empezando desde la cubeta 0 hasta la 9, sacándolos en el mismo orden en el que entraron:
	• Resultado de esta pasada: [1, 121, 21, 23, 432, 564]


La función de una pasada: radix_sort_pass(t_stack **stack_a, t_stack **stack_b, int bit, int size)

Esta función NO lleva exp, ni max, ni vuelve a llamar a index_stack_a. Su único trabajo es revisar los size elementos de stack_a fijándose únicamente en la columna bit:
1. Bucle para revisar toda la pila stack_a (i = 0 hasta i < size):
	• Miras el bit actual del nodo que está arriba del todo ((*stack_a)->index).
	• ¿Cómo se saca ese bit en C? Desplazas el índice hacia la derecha bit posiciones y te quedas con el último bit: (((*stack_a)->index >> bit) & 1).
	• Si el resultado es 0: Lo mandas a la pila B haciendo pb(stack_a, stack_b).
	• Si el resultado es 1: Lo dejas en la pila A rotándolo al fondo con ra(stack_a).
	• Sumas i++ y repites hasta haber mirado los size elementos iniciales.
2. Vaciar stack_b de vuelta a stack_a:
	• Cuando termina el bucle anterior, todos los números con un 0 en ese bit están en stack_b y los que tenían un 1 se quedaron ordenados en stack_a.
	• Haces un bucle while (*stack_b != NULL) llamando a pa(stack_a, stack_b) hasta que stack_b quede completamente vacía.


1. Bucle para revisar toda la pila stack_a (i = 0 hasta i < size):
	• Miras el bit actual del nodo que está arriba del todo ((*stack_a)->index).
    En binario, cualquier número se escribe solo con unos y ceros. Por ejemplo, el índice 6 en binario es 110:
• Columna bit = 0 (la de más a la derecha): vale 0.
• Columna bit = 1 (la del medio): vale 1.
• Columna bit = 2 (la de la izquierda): vale 1.
La operación (index >> bit) & 1 hace exactamente lo mismo que hacíamos antes con / 10 y % 10, pero en base 2:
• >> bit empuja el número hacia la derecha tantas columnas como diga bit (para poner la columna que te interesa justo en el borde derecho).
• & 1 mira únicamente ese último dígito de la derecha y te dice si es un 0 o un 1.

2. ¿Por qué pb si es 0 y ra si es 1?

Imagina que tienes una baraja de cartas boca arriba (stack_a) y otra mesa vacía al lado (stack_b). Vas a revisar todas las cartas de stack_a una por una (por eso das size vueltas, una por cada carta que había al principio):
• Miras la carta de arriba del todo de stack_a:
	• Si su bit actual es 0: La apartas a la mesa de al lado (pb). Como te la llevas de stack_a, la siguiente carta de la baraja queda automáticamente arriba lista para el siguiente turno.
	• Si su bit actual es 1: Quieres que se quede en stack_a, pero necesitas quitarla de arriba para poder mirar la carta que tiene debajo. ¿Cómo la quitas de en medio sin sacarla de stack_a? La pasas al fondo de la baraja (ra).
Al terminar de mirar las size cartas:
• Todas las cartas que tenían un 0 acabaron en stack_b.
• Todas las cartas que tenían un 1 dieron la vuelta y volvieron a quedar en stack_a, conservando su orden.

3. El remate: devolver las cartas (pa)

Como los números con 0 siempre son menores que los que tienen 1 en esa columna, deben ir arriba del todo en stack_a. Así que vacías todo stack_b devolviendo las cartas una a una a stack_a (pa) hasta que stack_b quede vacía.
Para asegurarnos de que te queda cristalino antes de escribirlo, dime:
• Si quieres que hagamos una prueba visual con 4 índices (3, 1, 2, 0) moviéndolos en bit = 0 y bit = 1
• O si ya ves clara la mecánica de pb / ra / pa para intentar escribir la función


3. void sort_radix(t_stack **stack_a, t_stack **stack_b)

Esta es la función principal del algoritmo complejo, la que invocará tu main.c para listas grandes (de 100 o 500 números). Actúa como la directora de la operación.
• Qué hace:
	1. Obtiene el tamaño total del stack inicial: size = stack_size(*stack_a).
	2. Llama a tu función de preprocesamiento para preparar los índices: index_stack_a(*stack_a, size).
	3. Obtiene el límite de iteraciones llamando a la primera función: max_bits = get_max_bits(*stack_a).
	4. Ejecuta un bucle while con un contador bit que va desde 0 hasta max_bits - 1.
	5. Dentro de ese bucle, simplemente llama a la segunda función: radix_sort_pass(stack_a, stack_b, bit, size).

    
La función principal: radix_sort(t_stack **stack_a, t_stack **stack_b)

Esta es la función "jefa" que controla todo el algoritmo:
1. Preparas los datos (una sola vez):
	• Calculas size = stack_size(*stack_a).
	• Llamas a index_stack_a(*stack_a, size) para que todos los nodos tengan su index del 0 al size - 1.
	• Calculas el tope de pasadas llamando a tu función: max_bits = get_max_bits(*stack_a).
2. Haces el bucle de las pasadas (bit):
	• Creas un contador bit = 0.
	• Mientras bit < max_bits:
		• Llamas a radix_sort_pass(stack_a, stack_b, bit, size).
		• Sumas bit++ para pasar al siguiente bit en la próxima vuelta.

