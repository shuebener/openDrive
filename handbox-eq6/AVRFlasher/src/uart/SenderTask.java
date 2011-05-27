
package uart;

import java.io.*;
import crc.*;
import gui.*;

public class SenderTask implements Runnable {

	Thread thread = null;
	int PortNr = -1;
	AVRFlasherGUI guih = null;
	
	
	public SenderTask(int iPortNr, AVRFlasherGUI gui) {
		this.PortNr = iPortNr;
		this.guih = gui;
		
		if(this.thread == null){
			this.thread = new Thread(this,"SenderTask");
			this.thread.start();
			this.guih.add2Lognl("Thread gestartet...");
			System.out.println("Thread gestartet...");
		}		
	}
	
	public synchronized void stop(){
		//thread.stop();
		if(this.thread != null) {
			this.thread = null;
			this.guih.add2Lognl("Thread gestoppt...");
			System.out.println("Thread gestoppt...");
			RS232.stopSenderTaskThread(this.PortNr);
			this.guih.setTestBtnEnabled(true);
		}
	}	
	
	
	public void run() {
		String ResponseMsg;
		double Prozent=0;
		
		try {
			int rows = misc.getLineCnt(guih.getSelectedFileName());
			
			FileReader fr = new FileReader(guih.getSelectedFileName());
			LineNumberReader br = new LineNumberReader(fr);
			CRC16 c = new CRC16();
			boolean ValidResponse = false;

			while(this.thread != null) {
				String line = br.readLine();
				if(line == null) {break;}
				
				c.reset();
				c.calc_crc16(line);
                              

				Prozent = Math.round(((100.0/(double)rows)*(double)br.getLineNumber())*10.0)/10.0;
				this.guih.add2Log("Sending ("+ Prozent +"%) ..");
				for(int i=0; i<10; i++) {
					ValidResponse=false;
					//guih.add2Lognl(line +" -> 0x"+ misc.Int2HexString(c.value));
					
					RS232.SendString(PortNr, line +" -> 0x"+ misc.Int2HexString(c.value) +"\n");
					this.guih.add2Log(".");
					
					while(true) {
						ResponseMsg = RS232.getReceivedData(this.PortNr);
						if(!ResponseMsg.equals("")) {break;}
					}

					if(ResponseMsg.equals("A")) {						
						ValidResponse=true;
						break;
					}
					else {
						ValidResponse=false;
						continue;
					}					
				}
				
				if(ValidResponse) {
					this.guih.add2Log(" OK\n");
				} else {
					this.guih.add2Log(" failed\n");
					this.guih.showErrorMsg("Fehler bei der Übertragung!\nBitte wiederholen!");
					System.out.println("Fehler bei der übertragung!");
					break;
				}
			}
			br.close();


		} catch(Exception e) {}			

		this.stop();
	}    
}
