
public class NumericRepresentation4 {
    public static void main(String[] args){
        double x = 0.125;
        double sum = 0;
        for(int i = 0; i < 80000; i++){
            sum += x;
        }
        double d = 10000 - sum;
        System.out.println(d);
    }
}