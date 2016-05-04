

//////////////////////////////////////////////////////////////
//
// This class creates and manages the messaging to the Hex Bug
//
// Created: Chip Audette, May-June 2014
//
///////////////////////////////////////////////////////////////

class HexBug {
  
   //FOR INTERNET DEBUG
   private int data;
   
   private int wait_millis = 5;
   private boolean fireBetweenMoves = false;
  
  //create inner class to wrap up a "command"
  class Command {
    private String command_str;
    private String name;
    private int counter;
    private Serial serial_h;
    public boolean printReceivedCommand = false;
    public int ID;
    
    Command(Serial _serial_h, String _str, String _name, int _ID) {
      serial_h = _serial_h;
      command_str = _str;
      name =_name;
      counter = 0;
      ID = _ID;
    }
    
    public int issue() {
      counter++;
      if (printReceivedCommand) println("HexBug: Command: " + name + " (" + counter + ")");
      if (serial_h != null) serial_h.write(command_str);
      return ID;
    }
  } //close definition of class Command
    
  private Command command_forward, command_climb, command_dive, command_left, command_right; 
  private int prev_command = -1;
  
  //Constructor, pass in an already-opened serial port
  HexBug(Serial serialPort) {
    int ID = 0;
    command_forward = new Command(serialPort,"O","Swim!",ID++);
    command_right = new Command(serialPort,"|","Right",ID++);
    command_left = new Command(serialPort,"{","Left",ID++);
    command_climb = new Command(serialPort,"}","Climb",ID++);
    command_dive = new Command(serialPort,"PO","Dive",ID++);
  }
  
  public void climb() {
    prev_command = command_climb.issue();
  }
  public void dive() {
    prev_command = command_dive.issue();
    
    //Connect to the Internet
    if( data == 1){
      String lines[] = loadStrings("http://one-billion-cat.com/test/openbci/index.php?p=0");
      for (int i = 0 ; i < lines.length; i++) {
        println(lines[i]);
      }
      data = 0;
    } else {
      String lines[] = loadStrings("http://one-billion-cat.com/test/openbci/index.php?p=1");
      for (int i = 0 ; i < lines.length; i++) {
        println(lines[i]);
      }
      data = 1;
    }
  }
  public void forward() {
    //if (fireBetweenMoves & (prev_command != command_forward.ID)) {
    //  prev_command = command_fire.issue();  //issue a FIRE command on a transition
    //  waitMilliseconds(wait_millis);
    //}
    prev_command = command_forward.issue();
  }
  public void left() {
    //if (fireBetweenMoves & (prev_command != command_left.ID)) {
    //  prev_command = command_fire.issue();  //issue a FIRE command on a transition
    //  waitMilliseconds(wait_millis);
    //}
    prev_command = command_left.issue();
  }
  public void right() {
    //if (fireBetweenMoves & (prev_command != command_right.ID)) {
    //  prev_command = command_fire.issue();  //issue a FIRE command on a transition
    //  waitMilliseconds(wait_millis);
    //}
    prev_command = command_right.issue();
  }
  
  public void waitMilliseconds(int dt_millis) {
      int start_time = millis();
      int t = millis();
      while (t-start_time < dt_millis) {
        t = millis();
      }
  }

}
