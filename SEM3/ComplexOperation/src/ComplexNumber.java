public class ComplexNumber {
    private double real;
    private double imaginary;

    public ComplexNumber(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    public double getImaginary() {
        return imaginary;
    }

    public double getReal() {
        return real;
    }

    @Override
    public String toString() {
        if(imaginary==0)
            return String.valueOf(real);
        if(real==0)
            return imaginary+"*i";
        String sign = imaginary >= 0 ? "+" : "";
        return real+sign+imaginary+"*i";

    }
}
