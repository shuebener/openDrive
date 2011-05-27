
package gui;
import uart.*;

public class GetSysInfo_Thread implements Runnable {
	
	protected String PortName = null;
	protected AVRFlasherGUI guih = null;
	
	public GetSysInfo_Thread(AVRFlasherGUI gui, String pname) {
		this.guih = gui;
		this.PortName = pname;

		return;
	}
	
	public void setPortName(String pname) {
		this.PortName = pname;
		return;
	}
		
	@Override
	public void run() {
		boolean ValidResponse = false;
		String ResponseMsg = null;
			
		for(int i=0; i<4; i++) {
			try {
				RS232.semaphore.acquire();
				System.out.println("semaphore.acquire()");
				
				ValidResponse=false;
				//guih.add2Lognl(line +" -> 0x"+ misc.Int2HexString(c.value));

				RS232.SendString(this.PortName, ":getSysInfo#");
				//this.guih.add2Log(".");

				ResponseMsg = null;
				long before =System.currentTimeMillis();
				while(true && System.currentTimeMillis() < (before + 25)) {
					//waiting max. 25ms for response
					ResponseMsg = RS232.getReceivedData(this.PortName);
					if(!ResponseMsg.equals("")) {break;} 

					try {Thread.sleep(0,100000);}//0.1ms
					catch(InterruptedException e) {}			
				}
				
				System.out.println("Test: "+ ResponseMsg);

				if(ResponseMsg.equals("A")) {						
					ValidResponse=true;
					break;
				}
				else {
					ValidResponse=false;
					continue;
				}
			
			} catch ( InterruptedException e ) {
				System.out.println("InterruptedException");
				e.printStackTrace();
			} finally {
				RS232.semaphore.release();
				System.out.println("semaphore.release()");
			}			
					
			if(!ValidResponse) {
				//wait for 100ms until next try...
				try {Thread.sleep(100);}
				catch(InterruptedException e) {}
			}
			
		}
		
		if(!ValidResponse) {
			System.out.println("Error: No valid response from device...");
			
			//RS232.CloseConnection(this.PortName);
			//this.guih. .btn_Connect.setText("Connect");
			//this.add2Lognl("Connection to "+ this.PortName +" closed.");			
		}
	}
		
}
