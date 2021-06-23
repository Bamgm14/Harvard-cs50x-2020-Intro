package in.co.bamgm14.digimon;

import androidx.annotation.NonNull;

/**
 * A class that represents a Digimon
 * <p>
 * Setter methods are missing. Object can only be created via constructor.
 * Member variables are private but getters are public to ensure the data can be accessed but not changed later.
 * <p>
 * This makes this data object immutable.
 */
public class Digimon {

    @NonNull
    private String name;

    @NonNull
    private String type;

    @NonNull
    private String stage;

    @NonNull
    private Double experience;

    @NonNull
    private Double bond;

    @NonNull
    private String imageUrl;

    public Digimon(
            @NonNull String name,
            @NonNull String type,
            @NonNull String stage,
            @NonNull Double experience,
            @NonNull Double bond,
            @NonNull String imageUrl
    ) {
        this.name = name;
        this.type = type;
        this.stage = stage;
        this.experience = experience;
        this.bond = bond;
        this.imageUrl = imageUrl;
    }

    public String getName() {
        return name;
    }

    public String getType() {
        return type;
    }

    public String getStage() {
        return stage;
    }

    public Double getExperience() {
        return experience;
    }

    public Double getBond() {
        return bond;
    }

    public String getImageUrl() {
        return imageUrl;
    }
}
