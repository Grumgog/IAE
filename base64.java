/*
 * Данный класс предназначен для кодирования/декодирования информации в/из BASE64
 */
package l.language;

public class Base64 {
    private static final String codeVector="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    private static final int mask1 = 0b111111;
    private static final int mask2 = 0b111111 << 6;
    private static final int mask3 = 0b111111 << 12;
    private static final int mask4 = 0b111111 << 18;
    public Base64()
    {
    }
    
    public static String toBase64(String message)
    {
        int len = message.length()/3;
        int zeroLen = message.length() - (len*3);
        if(zeroLen!=0)
            zeroLen = 3 - zeroLen;
        
        System.out.println("len " + len + "\nzerolen " + zeroLen);
        
        StringBuilder n = new StringBuilder("");
        int vector = 0;
        for(int i = 0; i<len; i++)
        {
            vector = (byte)message.charAt(i*3);
            vector = vector << 8;
            vector |= (byte)message.charAt((3*i)+1);
            vector = vector << 8;
            vector |= (byte)message.charAt((3*i)+2);
            n.append(codeVector.charAt((vector&mask4) >> 18));
            n.append(codeVector.charAt((vector&mask3) >> 12));
            n.append(codeVector.charAt((vector&mask2) >> 6));
            n.append(codeVector.charAt(vector&mask1));
        }
        if(zeroLen==1)
        {
            int lastindex = message.length()-1;
            int prevlastindex = lastindex-1;
            vector=(byte)message.charAt(prevlastindex);
            vector<<=8;
            vector|=(byte)message.charAt(lastindex);
            vector<<=8; // fill zero and move left
            n.append(codeVector.charAt((vector&mask4) >> 18));
            n.append(codeVector.charAt((vector&mask3) >> 12));
            n.append(codeVector.charAt((vector&mask2) >> 6));
            //n.append(codeVector.charAt(vector&mask1)); // equal instead zero bytes?
            n.append("=");
        }else if(zeroLen==2)
        {
            int lastindex = message.length()-1;
            vector=(byte)message.charAt(lastindex);
            vector<<=16; // fill zero and move left
            n.append(codeVector.charAt((vector&mask4) >> 18));
            n.append(codeVector.charAt((vector&mask3) >> 12));
            //n.append(codeVector.charAt((vector&mask2) >> 6));
            //n.append(codeVector.charAt(vector&mask1)); // equal instead zero bytes?
            n.append("==");
        }
        //n.reverse();
        return n.toString();
    }
    
    public static String toBase64(byte[] message)
    {
        int len = message.length/3;
        int zeroLen = message.length- (len*3);
        if(zeroLen!=0)
            zeroLen = 3 - zeroLen;
        
        System.out.println("len " + len + "\nzerolen " + zeroLen);
        
        StringBuilder n = new StringBuilder("");
        int vector = 0;
        for(int i = 0; i<len; i++)
        {
            vector = (byte)message[i*3];
            vector = vector << 8;
            vector |= (byte)message[(3*i)+1];
            vector = vector << 8;
            vector |= (byte)message[(3*i)+2];
            n.append(codeVector.charAt((vector&mask4) >> 18));
            n.append(codeVector.charAt((vector&mask3) >> 12));
            n.append(codeVector.charAt((vector&mask2) >> 6));
            n.append(codeVector.charAt(vector&mask1));
        }
        if(zeroLen==1)
        {
            int lastindex = message.length-1;
            int prevlastindex = lastindex-1;
            vector=(byte)message[prevlastindex];
            vector<<=8;
            vector|=(byte)message[lastindex];
            vector<<=8; // fill zero and move left
            n.append(codeVector.charAt((vector&mask4) >> 18));
            n.append(codeVector.charAt((vector&mask3) >> 12));
            n.append(codeVector.charAt((vector&mask2) >> 6));
            //n.append(codeVector.charAt(vector&mask1)); // equal instead zero bytes?
            n.append("=");
        }else if(zeroLen==2)
        {
            int lastindex = message.length-1;
            vector=(byte)message[lastindex];
            vector<<=16; // fill zero and move left
            n.append(codeVector.charAt((vector&mask4) >> 18));
            n.append(codeVector.charAt((vector&mask3) >> 12));
            //n.append(codeVector.charAt((vector&mask2) >> 6));
            //n.append(codeVector.charAt(vector&mask1)); // equal instead zero bytes?
            n.append("==");
        }
        //n.reverse();
        return n.toString();
    }
    
    //public byte[] decode(String message)
   // {
    //    int len = message.length()/4;
    //    byte[] outArray = new byte[len*3];
    //    int buffer = 0;
    ///    for(int i = 0; i<len; i++)
    //    {
    //        buffer = (byte)message.charAt((4*i));
     //       buffer<<=6;
    //        buffer |= (byte)message.charAt((4*i)+1);
     //       buffer<<=6;
    //        buffer |= (byte)message.charAt((4*i)+2);
    //        buffer<<=6;
     //       buffer |= (byte)message.charAt((4*i)+3);
            
     //   }
        
   //     return ;
   // }
}
