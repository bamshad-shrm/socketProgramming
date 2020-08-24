#!/usr/bin/perl

#Course: ET2504 Ht13 LP2 Computer Networking Software Tools
#Assignment: BE Perl; Assignment number 5a, (TCP chat client)    
#Student: Bamshad Gholamzadeh Shirmohammadi (Pn: 860322-5338)

use IO::Socket::INET;

if (@ARGV != 3) 
{
print "Wrong number of arguments. It should be like: <Ip Address> <Port Number> <Nick Name>\n";
exit();
}
 
my ( $kidpid, $recieve , $client_sock,$send,$message );
my $Nickname = $ARGV[2];
my $newline = "\n";

# Implementation of first step of the protocol: "connect". 
$client_sock = IO::Socket::INET->new( Proto=> "tcp",PeerAddr => $ARGV[0],PeerPort => $ARGV[1] ) or die "Can't connect to port\n";

# Implementation of second step of the protocol: "Recieveing a Hello version from server".
$client_sock->recv($recieve, 1024);
chomp($recieve);
if ($recieve eq "HELLO 1") 
{
print "The $recieve is recieved from server\n";
}
else
{
print "the Hello version is not sent so we will be discunnected\n";
exit();
}
# Implementation of third step of the protocol: "Sending a Nickname to server".
$send = "NICK ".$Nickname."";
$client_sock->send($send);
# Implementation of fourth step of the protocol: "Recieving OK/ERROR text from server".
$client_sock->recv($recieve, 1024);
chomp($recieve);
if($recieve eq "OK")
{
print "Now you are loged in to the server, so you can enter your message:\n";
}
else
{
print "$recieve\n";
exit();
}

die "can't fork: $!" unless defined( $kidpid = fork() );
	     
if ($kidpid) 
{
## Puting the client sucket to standard output.
## Implementation of sixth step of the protocol: "Recieving MSG nick text/ERROR text". 
 while ( defined( $recieve = <$client_sock> ) ) 
 {  
  chomp($recieve);
  $message=substr $recieve, 3;
  print "".$message."\n";		    
 } 
} 
## The child process,   
else 
{
## Putting standard input to the socket 
 while ( defined( $message = <STDIN> ) ) 
 {
  chomp ($message);
  $message= "".$message."".$newline."";
  $send = "MSG ".$message."";
## Implementation of fifth step of the protocol: "Sending MSG text to the server".
  $client_sock->send($send);
 }  
} 

