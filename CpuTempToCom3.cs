using System;
using System.Threading;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OpenHardwareMonitor.Hardware;
using System.IO.Ports;

namespace Get_CPU_Temp5
{
    class Program
    {
        public class UpdateVisitor : IVisitor
        {
            public void VisitComputer(IComputer computer)
            {
                computer.Traverse(this);
            }
            public void VisitHardware(IHardware hardware)
            {
                hardware.Update();
                foreach (IHardware subHardware in hardware.SubHardware) subHardware.Accept(this);
            }
            public void VisitSensor(ISensor sensor) { }
            public void VisitParameter(IParameter parameter) { }
        }

        static SerialPort SP;
        static void GetSystemInfo()
        {
            SP = new SerialPort();
            SP.PortName = "com3";
            SP.BaudRate = 9600;
            SP.ReadTimeout = 500;
            SP.Open();

            UpdateVisitor updateVisitor = new UpdateVisitor();
            Computer computer = new Computer();
            computer.Open();
            computer.CPUEnabled = true;
            computer.Accept(updateVisitor);
            for (int i = 0; i < computer.Hardware.Length; i++)
            {
                if (computer.Hardware[i].HardwareType == HardwareType.CPU)
                {
                    for (int j = 0; j < computer.Hardware[i].Sensors.Length; j++)
                    {
                        if (computer.Hardware[i].Sensors[j].SensorType == SensorType.Temperature)
                        {
                            Console.WriteLine(computer.Hardware[i].Sensors[j].Value.ToString());
                            SP.WriteLine(computer.Hardware[i].Sensors[j].Value.ToString());
                        }
                            
                    }
                }
            }
            computer.Close();
            SP.Close();
        }
        static async Task Main(string[] args)
        {
            
            while (true)
            {
                GetSystemInfo();
                await Task.Delay(2000);
            }
        }
    }
}