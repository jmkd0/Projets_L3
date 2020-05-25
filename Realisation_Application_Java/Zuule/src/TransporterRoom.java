import java.util.Random;

public class TransporterRoom {
	private UserInterface gui;
    private Room rooms[] = new Room[7];


    public TransporterRoom(UserInterface gui, Room[] rooms)
    {
    	gui.println("He are been transported succefully1 "+rooms.length);
    	for(int i=0; i<rooms.length; i++) {
    		this.rooms[i] = rooms[i];
    	}
    	gui.println("He are been transported succefully");
    	this.gui = gui;
    	Room nextRoom = getExit();
    	setTransport(nextRoom);
    }

   
    private void setTransport(Room room) {
    	gui.println("You are been transported succefully");
    	gui.engine.currentRoom = room;
        gui.println(room.getLongDescription());
        if(room.getImageName() != null)
           gui.showImage(room.getImageName());
    }
    
    public Room getExit() {
    	Random rand = new Random();
        // always return a random room
        return this.rooms[rand.nextInt(this.rooms.length)];
    }
}