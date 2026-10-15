public class Division implements ComplexOperation {
    @Override
    public ComplexNumber execute(ComplexNumber a, ComplexNumber b) {
        double impartitor = b.getReal() * b.getReal() + b.getImaginary() * b.getImaginary();
        if (impartitor == 0) {
            return new ComplexNumber(0,0);
        }
        double real = (a.getReal() * b.getReal() + a.getImaginary() * b.getImaginary()) / impartitor;
        double imaginary = (a.getImaginary() * b.getReal() - a.getReal() * b.getImaginary()) / impartitor;

        return new ComplexNumber(real, imaginary);
    }
}