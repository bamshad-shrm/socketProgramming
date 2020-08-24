use IO::Socket::INET;
 

$ipaddr = $ARGV[0];
$PORTNO  = $ARGV[1];


 
# creating a listening socket
my $socket = new IO::Socket::INET (
    LocalHost => $ipaddr,
    LocalPort => $PORTNO,
    Proto => 'tcp',
    Listen => 5,
    Reuse => 1
);
die "cannot create socket $!\n" unless $socket;
print "server waiting for client\n";
 



    # waiting for a new client connection
    my $client_socket = $socket->accept();
 
    # get information about a newly connected client
    my $client_address = $client_socket->peerhost();
    my $client_port = $client_socket->peerport();
    print "connection from $client_address:$client_port\n";


while(1)
{
 
    # read up to 1024 characters from the connected client
    my $data = "";
    $client_socket->recv($data, 1024);
    print "received data: $data\n";
 
    # write response data to the connected client
    $client_socket->send($data);
 

}
 

