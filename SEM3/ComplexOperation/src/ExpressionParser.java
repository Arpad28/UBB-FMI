public class ExpressionParser {

    public static boolean isValidExpression(String[] args) {
        if (args.length < 3 || args.length % 2 == 0) {
            return false;
        }
        String mainOperator = args[1];
        for (int i = 1; i < args.length; i += 2) {
            if (!args[i].equals(mainOperator)) {
                return false;
            }
        }
        return true;
    }

    public static ComplexNumber parseNumber(String s) {
        s = s.replace("*", "");
        if (!s.contains("i")) {
            return new ComplexNumber(Double.parseDouble(s), 0);
        }
        int splitIndex = -1;
        for (int i = s.length() - 1; i > 0; i--) {
            if (s.charAt(i) == '+' || s.charAt(i) == '-') {
                splitIndex = i;
                break;
            }
        }
        if (splitIndex > 0) {
            double real = Double.parseDouble(s.substring(0, splitIndex));
            String imagStr = s.substring(splitIndex).replace("i", "");
            if (imagStr.equals("+"))
                imagStr = "1";
            if (imagStr.equals("-"))
                imagStr = "-1";
            return new ComplexNumber(real, Double.parseDouble(imagStr));
        }
        else {
            String imagStr = s.replace("i", "");
            if (imagStr.isEmpty() || imagStr.equals("+"))
                imagStr = "1";
            if (imagStr.equals("-"))
                imagStr = "-1";
            return new ComplexNumber(0, Double.parseDouble(imagStr));
        }
    }

    public static ComplexNumber evaluate(String[] args) {
        ComplexNumber result = parseNumber(args[0]);
        ComplexOperation operation = OperationFactory.getOperation(args[1]);
        if (operation == null) {
            return new ComplexNumber(0, 0);
        }
        for (int i = 2; i < args.length; i += 2) {
            ComplexNumber nextNumber = parseNumber(args[i]);
            result = operation.execute(result, nextNumber);
        }
        return result;
    }
}