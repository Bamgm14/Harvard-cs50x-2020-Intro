package in.co.bamgm14.digimon;

import android.util.Log;

import org.json.JSONObject;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;

public class Interface {
    public static final int REGISTER = 0;
    public static final int PLAY = 1;
    public static final int PVE = 2;
    public static final int DIGIVOLVE = 3;
    public String code;
    public JSONObject Digimon;
    public String getcode(){
        return this.code;
    }
    public JSONObject getDigimon(){
        return this.Digimon;
    }
}
