using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace cs4_2
{
    class Program
    {
        static void Main(string[] args)
        {
            ArrayList transport = new ArrayList();
            transport.Add(new Tanker(1000));
            transport.Add(new DryCargoShip(3000));
            transport.Add(new Liner(200));

            transport.Add(new AirFreighter(100));
            transport.Add(new AirLiner(150));

            transport.Add(new Bus(30));
            transport.Add(new Truck(50));
            transport.Add(new Minivan(2, 8));

            transport.Add(new FreightTrain(500));
            transport.Add(new PassengerTrain(300));

            foreach (var item in transport)
            {
                Console.WriteLine("{0}\n", item);
            }
        }

        abstract class Transport
        {
            public string Title { get; set; }
            public int AmountOfCargo { get; set; }
            public int NumberOfPassengers { get; set; }
        }

        abstract class AirTransport : Transport
        {
            public string Action = "fly";
        }

        abstract class WaterTransport : Transport
        {
            public string Action = "sail";
        }

        abstract class RoadTransport : Transport
        {
            public string Action = "go along the road";
        }

        abstract class RailTransport : Transport
        {
            public string Action = "go along the rails";
        }

        class Tanker : WaterTransport
        {
            public Tanker(int amountOfCargo)
            {
                AmountOfCargo = amountOfCargo;
            }

            public override string ToString()
            {
                return string.Format("Tanker can {0} and transport {1} tone of liquids", Action, AmountOfCargo);
            }
        }

        class DryCargoShip : WaterTransport
        {
            public DryCargoShip(int amountOfCargo)
            {
                AmountOfCargo = amountOfCargo;
            }

            public override string ToString()
            {
                return string.Format("Dry cargo ship can {0} and transport {1} tone of dry cargos", Action, AmountOfCargo);
            }
        }

        class Liner : WaterTransport
        {
            public Liner(int numberOfPassengers)
            {
                NumberOfPassengers = numberOfPassengers;
            }

            public override string ToString()
            {
                return string.Format("Liner can {0} and transport {1} passengers", Action, NumberOfPassengers);
            }
        }

        class AirFreighter : AirTransport
        {
            public AirFreighter(int amountOfCargo)
            {
                AmountOfCargo = amountOfCargo;
            }

            public override string ToString()
            {
                return string.Format("Airfreighter can {0} and transport {1} tone of cargos", Action, AmountOfCargo);
            }
        }

        class AirLiner : AirTransport
        {
            public AirLiner(int numberOfPassengers)
            {
                NumberOfPassengers = numberOfPassengers;
            }

            public override string ToString()
            {
                return string.Format("Air liner can {0} and transport {1} passengers", Action, NumberOfPassengers);
            }
        }

        class Bus : RoadTransport
        {
            public Bus(int numberOfPassengers)
            {
                NumberOfPassengers = numberOfPassengers;
            }

            public override string ToString()
            {
                return string.Format("Bus can {0} and transport {1} passengers", Action, NumberOfPassengers);
            }
        }

        class Truck : RoadTransport
        {
            public Truck(int amountOfCargo)
            {
                AmountOfCargo = amountOfCargo;
            }

            public override string ToString()
            {
                return string.Format("Truck can {0} and transport {1} tone of cargos", Action, AmountOfCargo);
            }
        }

        class Minivan : RoadTransport
        {
            public Minivan(int amountOfCargo, int numberOfPassengers)
            {
                AmountOfCargo = amountOfCargo;
                NumberOfPassengers = numberOfPassengers;
            }

            public override string ToString()
            {
                return string.Format("Minivan can {0}, transport {1} tone of cargos and {2} passengers", Action, AmountOfCargo, NumberOfPassengers);
            }
        }

        class PassengerTrain : RailTransport
        {
            public PassengerTrain(int numberOfPassengers)
            {
                NumberOfPassengers = numberOfPassengers;
            }

            public override string ToString()
            {
                return string.Format("Passenger train can {0} and transport {1} passengers", Action, NumberOfPassengers);
            }
        }

        class FreightTrain : RailTransport
        {
            public FreightTrain(int amountOfCargo)
            {
                AmountOfCargo = amountOfCargo;
            }

            public override string ToString()
            {
                return string.Format("Freight train can {0} and transport {1} tone of cargos", Action, AmountOfCargo);
            }
        }

    }

}