public class Epsilon{
    public static void main(String[] args){
        float e = 1;
        while(1 + e/2 > 1) e = e/2;
        System.out.println(e);
    }
}