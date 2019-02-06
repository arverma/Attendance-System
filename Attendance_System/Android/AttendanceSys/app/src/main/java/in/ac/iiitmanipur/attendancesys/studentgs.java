package in.ac.iiitmanipur.attendancesys;

public class studentgs {
    private String name;
    private String id;
    private String attendance;
    private String image;

    public studentgs(String image, String name, String id, String attendance){
        this.name = name;
        this.image = image;
        this.attendance = attendance;
        this.id =id;
    }

    public void setName(String name){
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setImage(String image){
        this.image = image;
    }

    public String getImage() {
        return image;
    }

    public void setId(String id){
        this.id = id;
    }

    public String getId() {
        return id;
    }

    public void setAttendance(String attendance){
        this.attendance = attendance;
    }

    public String getAttendance() {
        return attendance;
    }


    public studentgs(){

    }
}