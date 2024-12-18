#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/random-variable-stream.h"
#include "ns3/internet-module.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/aodv-module.h"
#include "ns3/olsr-module.h"
#include "ns3/dsdv-module.h"
#include "ns3/dsr-module.h"
#include "ns3/traffic-control-module.h"
#include "ns3/queue-disc.h"
#include "ns3/traffic-control-helper.h"
#include "ns3/traffic-control-layer.h"
#include <iostream>
#include "ns3/tcp-socket-factory.h"
#include "ns3/tcp-socket.h"
#include "ns3/inet-socket-address.h"
#include "ns3/netanim-module.h"
#include <iomanip>

using namespace ns3;
using namespace std;

NS_LOG_COMPONENT_DEFINE("MANET");

struct swifi
{
    string name;
    vector<string> mode;
    swifi(string name = "")
    {
        this->name = name;
    }
};
swifi swmode[10];
void InforMode()
{
    swmode[0] = swifi("802.11p (V2X)");
    swmode[0].mode = {  
                        "OfdmRate1_5MbpsBW5MHz",
                        "OfdmRate2_25MbpsBW5MHz",
                        "OfdmRate3MbpsBW5MHz",
                        "OfdmRate4_5MbpsBW5MHz",
                        "OfdmRate6MbpsBW5MHz",
                        "OfdmRate9MbpsBW5MHz",
                        "OfdmRate12MbpsBW5MHz",
                        "OfdmRate13_5MbpsBW5MHz",
                        "OfdmRate3MbpsBW10MHz",
                        "OfdmRate4_5MbpsBW10MHz",
                        "OfdmRate6MbpsBW10MHz",
                        "OfdmRate9MbpsBW10MHz",
                        "OfdmRate12MbpsBW10MHz",
                        "OfdmRate18MbpsBW10MHz",
                        "OfdmRate24MbpsBW10MHz",
                        "OfdmRate27MbpsBW10MHz",
                        "OfdmRate6Mbps",
                        "OfdmRate9Mbps",
                        "OfdmRate12Mbps",
                        "OfdmRate18Mbps",
                        "OfdmRate24Mbps",
                        "OfdmRate36Mbps",
                        "OfdmRate48Mbps",
                        "OfdmRate54Mbps"
                    };
    swmode[1] = swifi("802.11b (Wi-Fi b)");
    swmode[1].mode = {
                        "DsssRate1Mbps",
                        "DsssRate2Mbps",
                        "DsssRate5_5Mbps",
                        "DsssRate11Mbps"
                    };
    swmode[2] = swifi("802.11g (Wi-Fi g)");
    swmode[2].mode = {
                        "ErpOfdmRate6Mbps",
                        "ErpOfdmRate9Mbps",
                        "ErpOfdmRate12Mbps",
                        "ErpOfdmRate18Mbps",
                        "ErpOfdmRate24Mbps",
                        "ErpOfdmRate36Mbps",
                        "ErpOfdmRate48Mbps",
                        "ErpOfdmRate54Mbps"
                    };
    swmode[3] = swifi("802.11n (Wi-Fi n)");
    swmode[3].mode = {
                        "HtMcs0",
                        "HtMcs1",
                        "HtMcs2",
                        "HtMcs3",
                        "HtMcs4",
                        "HtMcs5",
                        "HtMcs6",
                        "HtMcs7",
                        "HtMcs8",
                        "HtMcs9",
                        "HtMcs10",
                        "HtMcs11",
                        "HtMcs12",
                        "HtMcs13",
                        "HtMcs14",
                        "HtMcs15",
                        "HtMcs16",
                        "HtMcs17",
                        "HtMcs18",
                        "HtMcs19",
                        "HtMcs20",
                        "HtMcs21",
                        "HtMcs22",
                        "HtMcs23",
                        "HtMcs24",
                        "HtMcs25",
                        "HtMcs26",
                        "HtMcs27",
                        "HtMcs28",
                        "HtMcs29",
                        "HtMcs30",
                        "HtMcs31"
                    };
    swmode[4] = swifi("802.11ac (Wi-Fi 5)");
    swmode[4].mode = {
                        "VhtMcs0",
                        "VhtMcs1",
                        "VhtMcs2",
                        "VhtMcs3",
                        "VhtMcs4",
                        "VhtMcs5",
                        "VhtMcs6",
                        "VhtMcs7",
                        "VhtMcs8",
                        "VhtMcs9"
                    };
    swmode[5] = swifi("802.11ax (Wi-Fi 6)");
    swmode[5].mode = {
                        "HeMcs0",
                        "HeMcs1",
                        "HeMcs2",
                        "HeMcs3",
                        "HeMcs4",
                        "HeMcs5",
                        "HeMcs6",
                        "HeMcs7",
                        "HeMcs8",
                        "HeMcs9",
                        "HeMcs10",
                        "HeMcs11"
                    };
    swmode[6] = swifi("802.11be (Wi-Fi 7)");
    swmode[6].mode = {
                        "EhtMcs0",
                        "EhtMcs1",
                        "EhtMcs2",
                        "EhtMcs3",
                        "EhtMcs4",
                        "EhtMcs5",
                        "EhtMcs6",
                        "EhtMcs7",
                        "EhtMcs8",
                        "EhtMcs9",
                        "EhtMcs10",
                        "EhtMcs11",
                        "EhtMcs12",
                        "EhtMcs13"
                    };
    cout<<setw(25)<<left<<"Wifi Standarad"<<"|"<<" Physical Mode\n";
    cout<<"---------------------------------------------------------------------------------------------------------------\n";
    for (int i=0;i<=6;i++)
    {
        int c1 = 24;
        cout<<setw(c1)<<left<<swmode[i].name<<right<<i<<"| ";
        for (long unsigned int j=0;j<swmode[i].mode.size();j++)
        {
            if (j%3==0 && j!= 0) cout<<"\n"<<setw(c1+3)<<right<<"| ";
            cout<<swmode[i].mode[j]<<" - "<<j<<", ";
        }
        cout<<"\n---------------------------------------------------------------------------------------------------------\n";    
    }
}

class manetNetwork {
public:
    InternetStackHelper routingFunction(string route) {
        InternetStackHelper internet;
        if (route == "aodv") {
            AodvHelper aodv;
            internet.SetRoutingHelper(aodv);
        }
        if (route == "olsr") {
            OlsrHelper olsr;
            internet.SetRoutingHelper(olsr);
        }
        if (route == "dsdv") {
            DsdvHelper dsdv;
            internet.SetRoutingHelper(dsdv);
        }
        return internet;
    }

    void createNetwork() {
        string routing;
        double simulationTime = 500;
        uint32_t numNodes = 0;
        Time::SetResolution(Time::NS);

        // Step 1 - Creation of Nodes
        cout << "Please enter the number of nodes: ";
        cin >> numNodes;
        if (numNodes <= 1) {
            // end the program
            cout << "Ending simulation..." << endl;
            exit(0);
        }
        
        NodeContainer nodes; // creating nodes
        nodes.Create(numNodes);

        // Create mobility models
        // MobilityHelper mobility;
        // mobility.SetPositionAllocator("ns3::RandomDiscPositionAllocator",
        //                               "X", StringValue("100.0"),
        //                               "Y", StringValue("100.0"),
        //                               "Rho", StringValue("ns3::UniformRandomVariable[Min=0|Max=100]"));
        // mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
        // mobility.Install(nodes);

        MobilityHelper mobilityAdhoc;
        int64_t streamIndex = 0; // used to get consistent mobility across scenarios

        ObjectFactory pos;
        pos.SetTypeId("ns3::RandomRectanglePositionAllocator");
        pos.Set("X", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=200.0]"));
        pos.Set("Y", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=200.0]"));

        Ptr<PositionAllocator> taPositionAlloc = pos.Create()->GetObject<PositionAllocator>();
        streamIndex += taPositionAlloc->AssignStreams(streamIndex);

        std::stringstream ssSpeed;
        ssSpeed << "ns3::UniformRandomVariable[Min=0.0|Max=20.0]";
        std::stringstream ssPause;
        ssPause << "ns3::ConstantRandomVariable[Constant=0.0]";
        mobilityAdhoc.SetMobilityModel("ns3::RandomWaypointMobilityModel",
                                    "Speed",
                                    StringValue(ssSpeed.str()),
                                    "Pause",
                                    StringValue(ssPause.str()),
                                    "PositionAllocator",
                                    PointerValue(taPositionAlloc));
        mobilityAdhoc.SetPositionAllocator(taPositionAlloc);
        mobilityAdhoc.Install(nodes);
        streamIndex += mobilityAdhoc.AssignStreams(nodes, streamIndex);

        // Get the positions of the nodes
        for (uint32_t i = 0; i < nodes.GetN(); ++i) {
            Ptr<Node> node = nodes.Get(i);
            Vector pos = node->GetObject<MobilityModel>()->GetPosition();
            std::cout << "Node " << node->GetId() << " position: " << pos.x << ", " << pos.y << std::endl;
        }

        // Create wireless network
        InforMode();
        std::cout << "Enter the Wifi Standard: ";
        int wS;
        std::cin >> wS;
        WifiHelper wifi;
        switch (wS)
        {
            case 0:
                wifi.SetStandard(WIFI_STANDARD_80211p);
                cout<<"Wifi Standard is "<< swmode[0].name<<"\n";
                break;
            case 1:
                wifi.SetStandard(WIFI_STANDARD_80211b);
                cout<<"Wifi Standard is "<< swmode[1].name<<"\n";
                break;
            case 2:
                wifi.SetStandard(WIFI_STANDARD_80211g);
                cout<<"Wifi Standard is "<< swmode[2].name<<"\n";
                break;
            case 3:
                wifi.SetStandard(WIFI_STANDARD_80211n);
                cout<<"Wifi Standard is "<< swmode[3].name<<"\n";
                break;
            case 4:
                wifi.SetStandard(WIFI_STANDARD_80211ac);
                cout<<"Wifi Standard is "<< swmode[4].name<<"\n";
                break;
            case 5:
                wifi.SetStandard(WIFI_STANDARD_80211ax);
                cout<<"Wifi Standard is "<< swmode[5].name<<"\n";
                break;
            case 6:
                wifi.SetStandard(WIFI_STANDARD_80211be);
                cout<<"Wifi Standard is "<< swmode[6].name<<"\n";
                break;
            default:
                cout<<"Wifi Standard isn't valid!"<<endl;
                exit(1);
                break;    
        }
        
        string DataMode = "OfdmRate6Mbps";
        string ControlMode = "OfdmRate6Mbps";
        int choice = 0;
        cout<<"Enter DataMode: "; 
        cin>>choice;
        DataMode = swmode[wS].mode[choice];
        cout<<"DataMode is "<<DataMode<<"\n";
        cout<<"Enter ControlMode: "; 
        cin>>choice;
        ControlMode = swmode[wS].mode[choice];
        cout<<"ControlMode is "<<ControlMode<<"\n"; 
        wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager",
                                     "DataMode", StringValue(DataMode),
                                     "ControlMode", StringValue(ControlMode));
        YansWifiPhyHelper wifiPhy;
        YansWifiChannelHelper wChannel = YansWifiChannelHelper::Default();
        wifiPhy.SetChannel(wChannel.Create());
        WifiMacHelper wifiMac;
        wifiMac.SetType("ns3::AdhocWifiMac");
        NetDeviceContainer devices = wifi.Install(wifiPhy, wifiMac, nodes);

        // Input which routing protocol
        cout << "Enter the routing protocol (aodv,dsdv,olsr):";
        cin >> routing;
        InternetStackHelper internet;
        if (routing == "aodv") {
            AodvHelper aodv;
            internet.SetRoutingHelper(aodv);
            internet.Install(nodes);
            cout << "The routing protocol is: aodv" << endl;
        } else if (routing == "olsr") {
            OlsrHelper olsr;
            internet.SetRoutingHelper(olsr);
            internet.Install(nodes);
            cout << "The routing protocol is: olsr" << endl;
        } else if (routing == "dsdv") {
            DsdvHelper dsdv;
            internet.SetRoutingHelper(dsdv);
            internet.Install(nodes);
            cout << "The routing protocol is: dsdv" << endl;
        } else {
            cout << "Invalid routing protocol!" << endl;
            exit(1);
        }

        // Assign IP addresses
        Ipv4AddressHelper ipAddrs;
        ipAddrs.SetBase("192.168.1.0", "255.255.255.0");
        Ipv4InterfaceContainer ifaces = ipAddrs.Assign(devices);

        // Attach the FIFO queue to the device with a simple buffer
        TrafficControlHelper tch;
        tch.Install(devices);
        tch.SetRootQueueDisc("ns3::FifoQueueDisc");

        // Create applications
        uint16_t port = 9;
        UdpServerHelper server(port);
        ApplicationContainer serverApp = server.Install(nodes);
        serverApp.Start(Seconds(1.0));
        serverApp.Stop(Seconds(simulationTime));

        // Continuously sending packets from each node to a random node until simulation time is reached
        uint64_t packetCount = 10;
        double packetInterval = 0.01; // seconds
        double delay = 0; // seconds
        // double delayInterval = 0.05; // seconds
        for (uint64_t i = 0; i < nodes.GetN(); i++){ 
        // for (uint64_t i = 0; i<1; i++){
            Ptr<Node> sourceNode = nodes.Get(i);
            uint64_t destIndex = rand() % nodes.GetN();
            // Ensure that the node does not send a packet to itself
            while (destIndex == i) {
                destIndex = rand() % nodes.GetN();
            }
            Ptr<Node> destNode = nodes.Get(destIndex);
            // Get the IP address of the destination node
            Ipv4Address destAddr = destNode->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal();
            UdpClientHelper client(destAddr, port);
            client.SetAttribute("MaxPackets", UintegerValue(packetCount));
            client.SetAttribute("Interval", TimeValue(Seconds(packetInterval)));
            client.SetAttribute("PacketSize", UintegerValue(32));
            ApplicationContainer clientApp = client.Install(sourceNode);
            clientApp.Start(Seconds(2.0 + delay)); // Start sending packets with a delay
            // delay += delayInterval;
            clientApp.Stop(Seconds(2.0 + 8.0)); // Stop sending packets after the delay
            // delay += delayInterval;
        }

        // Install FlowMonitor onto the nodes
        FlowMonitorHelper flow;
        Ptr<FlowMonitor> monitor;
        monitor = flow.InstallAll();

        // Animation
        AnimationInterface anim("manet.xml");
        anim.SetMaxPktsPerTraceFile(50000);
        anim.EnablePacketMetadata();
        anim.EnableIpv4RouteTracking("manet_routing.xml", Seconds(0), Seconds(simulationTime), Seconds(1));
        anim.EnableWifiMacCounters(Seconds(0), Seconds(20));
        anim.EnableWifiPhyCounters(Seconds(0), Seconds(20));

        // Run simulation
        // Update simulation duration
        Simulator::Stop(Seconds(simulationTime+10));
        Simulator::Run();
        Simulator::Destroy();

        uint32_t processedFlows = 0;
        double SentPackets = 0;
        double ReceivedPackets = 0;
        double AvgThroughput = 0;
        double LostPackets = 0;
        Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier>(flow.GetClassifier());
        std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats();
        for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator iter = stats.begin(); iter != stats.end(); ++iter) {
            Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow(iter->first);
            if (processedFlows > numNodes) {
                break;
            }
            NS_LOG_UNCOND("----Flow ID:" << iter->first);
            NS_LOG_UNCOND("Source Address: " << t.sourceAddress << " Destination Address: " << t.destinationAddress);
            NS_LOG_UNCOND("Sent Packets=" << iter->second.txPackets);
            NS_LOG_UNCOND("Received Packets =" << iter->second.rxPackets);
            NS_LOG_UNCOND("Lost Packets =" << iter->second.txPackets - iter->second.rxPackets);
            NS_LOG_UNCOND("Throughput =" << iter->second.rxBytes * 8.0 / (iter->second.timeLastRxPacket.GetSeconds() - iter->second.timeFirstTxPacket.GetSeconds()) / 1024 << "Kbps");
            SentPackets = SentPackets + (iter->second.txPackets);
            ReceivedPackets = ReceivedPackets + (iter->second.rxPackets);
            LostPackets = LostPackets + (iter->second.txPackets - iter->second.rxPackets);
            AvgThroughput = AvgThroughput + (iter->second.rxBytes * 8.0 / (iter->second.timeLastRxPacket.GetSeconds() - iter->second.timeFirstTxPacket.GetSeconds()) / 1024);
            processedFlows++;
        }

        AvgThroughput = AvgThroughput / processedFlows;
        NS_LOG_UNCOND("--------Total Results of the simulation----------" << std::endl);
        NS_LOG_UNCOND("Total sent packets =" << SentPackets);
        NS_LOG_UNCOND("Total Received Packets =" << ReceivedPackets);
        NS_LOG_UNCOND("Total Lost Packets =" << LostPackets);
        NS_LOG_UNCOND("Packet delivery rate = " << ((ReceivedPackets * 100) / SentPackets) << "%");
        NS_LOG_UNCOND("Average Throughput =" << AvgThroughput << " Kbps");
        monitor->SerializeToXmlFile("manet_flow-monitor.xml", false, false);
    }
};

int main(int argc, char* argv[]) {
    manetNetwork my;
    my.createNetwork();
    return 0;
}