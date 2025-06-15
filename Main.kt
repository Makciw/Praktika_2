import java.util.Scanner

enum class FunctionOption {
    FERMA_AND_DECOMPOSITION,
    FIND_D,
    MOD_INVERSE,
    ENCRYPT_DECRYPT,
    SOLVE_EQUATION
}

fun main() {
    val scanner = Scanner(System.`in`)
    println("Введите номер функции (1–5):")
    val numF = scanner.nextInt()
    scanner.nextLine() // съедаем \n

    val option = when (numF) {
        1 -> FunctionOption.FERMA_AND_DECOMPOSITION
        2 -> FunctionOption.FIND_D
        3 -> FunctionOption.MOD_INVERSE
        4 -> FunctionOption.ENCRYPT_DECRYPT
        5 -> FunctionOption.SOLVE_EQUATION
        else -> {
            println("Неверный номер")
            return
        }
    }

    when (option) {
        FunctionOption.FERMA_AND_DECOMPOSITION -> {
            while (true) {
                try {
                    print("Введите a, x, p (через пробел): ")
                    val input = readLine()?.split(" ") ?: continue
                    if (input.size < 3) continue

                    val a = input[0].toInt()
                    val x = input[1].toInt()
                    val p = input[2].toInt()

                    checkInput(a, x, p)

                    println("Результат (Ферма): ${fermat(x, a, p)}")
                    println("Результат (бинарное разложение): ${decomposition(toBinary(x), a, p)}")
                } catch (e: Exception) {
                    System.err.println("Ошибка: ${e.message}")
                }
            }
        }

        FunctionOption.FIND_D -> {
            while (true) {
                try {
                    print("Введите число c: ")
                    val c = readLine()!!.toInt()
                    print("Введите модуль m: ")
                    val m = readLine()!!.toInt()

                    val d = findD(c, m)
                    println("Число d: $d")
                } catch (e: IllegalArgumentException) {
                    System.err.println("Ошибка ввода: ${e.message}")
                } catch (e: Exception) {
                    System.err.println("Неизвестная ошибка.")
                }
            }
        }

        FunctionOption.MOD_INVERSE -> {
            while (true) {
                try {
                    print("Введите число c: ")
                    val c = readLine()!!.toInt()
                    print("Введите модуль m: ")
                    val m = readLine()!!.toInt()

                    val inverse = modInverse(c, m)
                    println("Обратный элемент $c^(-1) mod $m = $inverse")
                } catch (e: IllegalArgumentException) {
                    System.err.println("Ошибка: ${e.message}")
                } catch (e: Exception) {
                    System.err.println("Неизвестная ошибка.")
                }
            }
        }

        FunctionOption.ENCRYPT_DECRYPT -> {
            val letters = mutableListOf<Int>()

            print("Введите путь до файла: ")
            val fileName = readLine() ?: return

            read(fileName, letters)
            val (encrypted, prime, secretKey) = encryption(letters)

            println("Зашифрованный текст хранится в файле: output.txt")
            encryptionWrite("output.txt", encrypted)

            val decryptedLetters = decryption(encrypted, prime, secretKey)
            println("Расшифрованный текст хранится в файле: res.txt")
            decryptionWrite("res.txt", decryptedLetters)
        }

        FunctionOption.SOLVE_EQUATION -> {
            val A = 1256
            val B = 847
            val C = 119
            val (gcd, a, b) = extendedGcd(A, B)
            if (gcd != 1) {
                println("Решения нет")
            } else {
                println("Решение уравнения: $A*${a * C} + $B*${b * C} = ${gcd * C}")
            }
        }
    }
}
