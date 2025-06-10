
import kotlin.math.sqrt
import java.io.File
import java.math.BigInteger
import java.security.SecureRandom
// 1
fun isPrime(p: Int): Boolean {
    if (p <= 1) return false
    if (p == 2) return true
    for (i in 2..sqrt(p.toDouble()).toInt()) {
        if (p % i == 0) return false
    }
    return true
}

fun fermatCond(a: Int, p: Int): Boolean {
    return isPrime(p) && (a % p != 0)
}

fun fermat(x: Int, a: Int, p: Int): Int {
    if (!fermatCond(a, p)) throw RuntimeException("Ошибка: нарушение условий теоремы Ферма (a и p должны быть взаимно просты)")
    return modPow(a, x, p)
}

// Быстрое возведение в степень по модулю
fun modPow(base_: Int, exponent_: Int, modulus_: Int): Int {
    var base = base_ % modulus_
    var exponent = exponent_
    var result = 1
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus_
        }
        base = (base * base) % modulus_
        exponent /= 2
    }
    return result
}

fun toBinary(x: Int): List<Int> {
    val binary = mutableListOf<Int>()
    var n = x
    while (n > 0) {
        binary.add(n % 2)
        n /= 2
    }
    return binary.reversed()
}

fun decomposition(binary: List<Int>, a: Int, p: Int): Int {
    var result = 1
    var base = a % p
    for (bit in binary) {
        if (bit == 1) {
            result = (result * base) % p
        }
        base = (base * base) % p
    }
    return result
}

fun checkInput(a: Int, x: Int, p: Int) {
    if (p <= 1 || !isPrime(p)) {
        throw RuntimeException("Ошибка: p должно быть простым числом > 1")
    }
    if (a % p == 0) {
        throw RuntimeException("Ошибка: a не должно делиться на p (условие теоремы Ферма)")
    }
    if (x < 0) {
        throw RuntimeException("Ошибка: степень x не может быть отрицательной")
    }
}

// 2
fun extendedGCD(a: Int, b: Int): Triple<Int, Int, Int> {
    if (a == 0) {
        return Triple(b, 0, 1)
    }

    val (gcd, x1, y1) = extendedGCD(b % a, a)
    val x = y1 - (b / a) * x1
    val y = x1

    return Triple(gcd, x, y)
}

fun findD(c: Int, m: Int): Int {
    val (gcd, u, _) = extendedGCD(c, m)

    if (gcd != 1) {
        throw RuntimeException("Решение не существует: c и m должны быть взаимно просты")
    } else {
        return ((u % m) + m) % m // корректировка на случай отрицательных значений
    }
}

// 3
fun modInverse(c: Int, m: Int): Int {
    val (gcd, x, _) = extendedGCD(c, m)

    if (gcd != 1) {
        throw RuntimeException("Обратного элемента не существует: c и m должны быть взаимно просты")
    } else {
        return ((x % m) + m) % m
    }
}

// 4
fun read(fileName: String, outputList: MutableList<Int>) {
    val letters = mutableListOf<Int>()
    val bytes = File(fileName).readBytes()
    for (b in bytes) {
        letters.add(b.toInt() and 0xFF)
    }
}

// Запись зашифрованных пар (BigInteger, BigInteger) в файл
fun encryptionWrite(fileName: String, letters: List<Pair<BigInteger, BigInteger>>) {
    File(fileName).bufferedWriter().use { writer ->
        letters.forEach { (first, second) ->
            writer.write("($first $second) ")
        }
    }
}

// Запись расшифрованных символов в файл
fun decryptionWrite(fileName: String, letters: List<Char>) {
    File(fileName).bufferedWriter().use { writer ->
        letters.forEach { c ->
            writer.write(c.toString())
        }
    }
}

// Генерация большого простого числа заданной битовой длины
fun largePrime(bits: Int): BigInteger {
    val rnd = SecureRandom()
    return BigInteger.probablePrime(bits, rnd)
}

// Возведение в степень по модулю
fun coolPow(base: BigInteger, exp: BigInteger, mod: BigInteger): BigInteger {
    return base.modPow(exp, mod)
}

// Поиск простых делителей n
fun getPrimeFactors(n: BigInteger): Set<BigInteger> {
    val factors = mutableSetOf<BigInteger>()
    var num = n
    var i = BigInteger.valueOf(2)
    while (i * i <= num) {
        while (num % i == BigInteger.ZERO) {
            factors.add(i)
            num /= i
        }
        i += BigInteger.ONE
    }
    if (num > BigInteger.ONE) {
        factors.add(num)
    }
    return factors
}

// Проверка, является ли g примитивным корнем по модулю p
fun isPrimitiveRoot(g: BigInteger, p: BigInteger, factors: Set<BigInteger>): Boolean {
    val phi = p - BigInteger.ONE
    for (q in factors) {
        val exp = phi / q
        val res = g.modPow(exp, p)
        if (res == BigInteger.ONE) return false
    }
    return true
}

// Поиск первого примитивного корня по модулю p
fun maxPrimitiveRoot(p: BigInteger): BigInteger {
    val phi = p - BigInteger.ONE
    val factors = getPrimeFactors(phi)
    var g = BigInteger.valueOf(2)
    while (g < p) {
        if (isPrimitiveRoot(g, p, factors)) return g
        g += BigInteger.ONE
    }
    throw RuntimeException("Не удалось найти примитивный корень по модулю p")
}

// Генерация случайного числа x в диапазоне [1, p-2]
fun generateX(p: BigInteger): BigInteger {
    val rnd = SecureRandom()
    val max = p - BigInteger.valueOf(2)
    var x: BigInteger
    do {
        x = BigInteger(max.bitLength(), rnd)
    } while (x < BigInteger.ONE || x > max)
    return x
}

// Шифрование
fun encryption(letters: List<Int>): Triple<List<Pair<BigInteger, BigInteger>>, BigInteger, BigInteger> {
    val bits = 49
    val p = largePrime(bits)
    val g = maxPrimitiveRoot(p)
    val x = generateX(p)
    val y = coolPow(g, x, p)
    val encrypLetters = mutableListOf<Pair<BigInteger, BigInteger>>()
    for (mInt in letters) {
        val m = BigInteger.valueOf(mInt.toLong())
        val k = generateX(p)
        val u = coolPow(g, k, p)
        val v = (m * coolPow(y, k, p)) % p
        encrypLetters.add(u to v)
    }
    return Triple(encrypLetters, p, x)
}

// Расшифровка
fun decryption(encrypLetters: List<Pair<BigInteger, BigInteger>>, p: BigInteger, x: BigInteger): List<Char> {
    val decipLetters = mutableListOf<Char>()
    for ((u, v) in encrypLetters) {
        val m = (v * coolPow(u, p - BigInteger.ONE - x, p)) % p
        decipLetters.add(m.toInt().toChar())
    }
    return decipLetters
}

// 5
fun extendedGcd(a: Int, b: Int): Triple<Int, Int, Int> {
    return if (b == 0) {
        Triple(a, 1, 0)  // (gcd, x, y)
    } else {
        val (d, x1, y1) = extendedGcd(b, a % b)
        val x = y1
        val y = x1 - (a / b) * y1
        Triple(d, x, y)
    }
}