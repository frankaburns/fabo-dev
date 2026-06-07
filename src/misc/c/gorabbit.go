package main

import (
    "log"
	"encoding/json"
//	"github.com/mitchellh/mapstructure"
    "github.com/streadway/amqp"
)
/*following is the msg that comes from EHM interface*/
type EhmIntfMsg struct {
	VxlanId        int32
	BridgeName     string
	TapInt	       string
	MacAddr	       string
	NfvIntf	       string
}
type AddNfvInfo struct {
     	MsgType	     string  //nfvDetails <-- this is the msg type to be used
	Cmd      string
	Args	     interface{}
}

func failOnError(err error, msg string) {
    if err != nil {
        log.Fatalf("%s: %s", msg, err)
    }
}

func main() {
    conn, err := amqp.Dial("amqp://guest:guest@localhost:5672/")
    failOnError(err, "Failed to connect to RabbitMQ")
    defer conn.Close()

    ch, err := conn.Channel()
    failOnError(err, "Failed to open a channel")
    defer ch.Close()

    q, err := ch.QueueDeclare(
        "rpc_agent_controller", // name
        false,   // durable
        false,   // delete when unused
        false,   // exclusive
        false,   // no-wait
        nil,     // arguments
    )
    failOnError(err, "Failed to declare a queue")
    intf1 := EhmIntfMsg {
	VxlanId: 1010,               //derived from bridge name -the last part of the name
	BridgeName: "br-vn1010",
	TapInt:"td_br-vn1010_1",
	MacAddr:"DE:AD:01:7e:04:8e",
	NfvIntf:"eth0",
}
    intf2 := EhmIntfMsg {
	VxlanId: 1015,
	BridgeName: "br-vn1015",
	TapInt:"td_br-vn1015_1",
	MacAddr:"LI:VE:01:7e:04:8e",
	NfvIntf:"eth0",
}
    intfArr := []EhmIntfMsg{intf1,intf2}
input := map[string]interface{}{
        "vlist": intfArr,
    }
 

    ehmMsg := AddNfvInfo{}
    ehmMsg.MsgType = "nfvDetails"
    ehmMsg.Cmd = "vwa"             //specifies what type of service it is may change later
    ehmMsg.Args = input
 
    body, err := json.Marshal(ehmMsg) 
//    body := "hello"
    err = ch.Publish(
        "",     // exchange
        q.Name, // routing key
        false,  // mandatory
        false,  // immediate
        amqp.Publishing{
		ContentType: "text/plain",
		//ContentType: "application/json",
		Body:        []byte(body), 
        })
    log.Printf(" [x] Sent %s", body)
    failOnError(err, "Failed to publish a message")
}
