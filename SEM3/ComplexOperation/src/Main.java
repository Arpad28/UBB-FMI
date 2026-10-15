public class Main {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Nu ai introdus argumente in linia de comanda");
            return;
        }

        if (ExpressionParser.isValidExpression(args)) {
            ComplexNumber result = ExpressionParser.evaluate(args);
            if (result != null) {
                System.out.println("Rezultatul este: " + result.toString());
            }
        } else {
            System.out.println("Expresia nu este valida");
        }
    }
}