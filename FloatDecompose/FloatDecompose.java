import java.util.*;

public class FloatDecompose {
    /**
     * @param value
     * @return
     */
    public static int getSign(float value) {
        int v = Float.floatToIntBits(value);
        return v >>> 31;
    } 


    /** 
     * @param value input value 
     * @return exponential value of 2. 
     */
    public static int getExponent(float value) {
        int v = Float.floatToIntBits(value);
        v = v << 1;
        v = v >>> 24;
        return v;
    } 



    public static int getFraction(float value) {
        int v = Float.floatToIntBits(value);
        v = v << 9;
        v = v >>> 9;
        return v;
    } 


    public static float makeFloat(int sign, int exp, int frac) {
        sign = sign << 31;
        exp = exp << 23;
        int result =  sign + exp + frac;
        return Float.intBitsToFloat(result);
    }


    /**
     * Helper method to change float to binaryString. 
     * @param f
     * @return
     */
    public static String floatToBinary(float f){
        int valueInt = Float.floatToIntBits(f); 
        String binaryString = Integer.toBinaryString(valueInt);
        return binaryString;
    }

    /**
     * Main method to run the program and to make tests. 
     * @param args
     */
    public static void main(String[] args) {
        // TODO: remove main before submit
        Scanner stdin = new Scanner(System.in);
        System.out.println("Hello World, please enter below: ");
        String userInputLine = stdin.nextLine();
        userInputLine.trim();
        float floatUser = Float.parseFloat(userInputLine);
        int floatToIntBis= Float.floatToIntBits(floatUser);
        System.out.println("The number is : "+floatToIntBis);
        System.out.println(floatToBinary(floatUser).length() +
         " @@ " + floatToBinary(floatUser));
         int getSignValue = getSign(floatUser);
         int getExpoValue = getExponent(floatUser);
         int getFraction = getFraction(floatUser);
        System.out.println(" The sign bit is: " + getSign(floatUser));
        System.out.println(" The exponent bits are : " + getExponent(floatUser));
        System.out.println(" The fraction is: " + getFraction(floatUser));
        System.out.println(" The float is :"+ makeFloat(getSignValue, 
        getExpoValue, getFraction));
    }
}