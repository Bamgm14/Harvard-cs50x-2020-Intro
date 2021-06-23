package in.co.bamgm14.digimon.data;

import androidx.annotation.NonNull;

public class Response {
    public static final String CODE_NONE = "None";

    @NonNull
    private String code;

    @NonNull
    private String message;

    Response(@NonNull String code, @NonNull String message) {
        this.code = code;
        this.message = message;
    }

    public String getCode() {
        return code;
    }

    public void setCode(String code) {
        this.code = code;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }
}
