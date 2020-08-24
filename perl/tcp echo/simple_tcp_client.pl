use IO::Socket::INET;


$ipaddr = $ARGV[0];
$PORTNO  = $ARGV[1];
my $response = ""; 
my $message;
 
# create a connecting socket
my $socket = new IO::Socket::INET (
    PeerHost => $ipaddr,
    PeerPort => $PORTNO,
    Proto => 'tcp',
);
die "cannot connect to the server $!\n" unless $socket;
print "connected to the server\n";
 
while(1)
{
$message = <STDIN>;

$socket->send($message);


$socket->recv($response, 1024);
print "server response: $response\n";
}
