public static BigInteger newton(BigInteger n) {
    BigInteger a = BigInteger.ONE.shiftLeft(n.bitLength() / 2);
    boolean isDec = false;
    while(true) {
        BigInteger b = n.divide(a).add(a).shiftRight(1);
        if (a.compareTo(b) == 0 || a.compareTo(b) < 0 && isDec)
            break;
        isDec = a.compareTo(b) > 0;
        a = b;
    }
    return a;
}
