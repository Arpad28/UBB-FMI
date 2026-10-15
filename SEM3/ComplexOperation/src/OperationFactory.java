public class OperationFactory {
    public static ComplexOperation getOperation(String operator) {
        if(operator.equals("+")) {
            return new Addition();
        } else if(operator.equals("-")) {
            return new Substraction();
        } else if(operator.equals("*")) {
            return new Multiplication();
        } else if(operator.equals("/")) {
            return new Division();
        } else {
            return null;
        }
    }
}
