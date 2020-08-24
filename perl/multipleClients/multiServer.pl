#!/usr/bin/perl

#Course: ET2504 Ht13 LP2 Computer Networking Software Tools
#Assignment: BE Perl; Assignment number 5b, (TCP chat server)    
#Student: Bamshad Gholamzadeh Shirmohammadi (Pn: 860322-5338)

use IO::Select;
use IO::Socket::INET; 
use strict;
#use warnings;
use 5.010;


if (@ARGV != 2) 
{
print "Wrong number of arguments. It should be like: <Ip Address> <Port Number>\n";
exit();
}

my ($server_sock, $sock , $receive , $new_sock , $readable_handles,$length,$first_chars, @nick_names, $number_of_user,$i,$current_user_number);

$number_of_user=0;

## Implementation of first step of the protocol: "connect".
$server_sock = new IO::Socket::INET( LocalAddr => $ARGV[0], LocalPort => $ARGV[1], Proto=> 'tcp', Listen=>20) or die "Could not connect: $!";

print "TCP chat server is waiting for clients.\n";    

$readable_handles = new IO::Select();
$readable_handles->add($server_sock);

while (1) 
{
 (my $new_readable) = IO::Select->select($readable_handles, undef, undef, 0);
 foreach $sock (@$new_readable)
 {
  if ($sock == $server_sock) 
  {
   $new_sock = $sock->accept() or die sprintf "ERROR (%d)(%s)(%d)(%s)", $!,$!,$^E,$^E;
   $readable_handles->add($new_sock);
   ## Implementation of second step of the protocol: "Sending Hello version to client".
   $new_sock->send("HELLO 1");
   ## Implementation of third step of the protocol: "Recieveing Nickname from client".
   $new_sock->recv($receive, 1024);
   $length=length($receive);

   $first_chars = substr($receive, 0, 4); 
   if($first_chars eq "NICK")
   {    
    if($length-5>12 )
    {
     ## Implementation of fourth step of the protocol: "Sendidng ERROR/OK to client".
     $new_sock->send("ERR The Nickname should not be longer than 12 characters, pleas try again");
     $readable_handles->remove($new_sock);
	 close($new_sock);		    
    }
    else
    {
     ## Implementation of fourth step of the protocol: "Sendidng ERROR/OK to client".
     $new_sock->send("OK");
     $nick_names[$number_of_user]=substr $receive, 5;
     print "A new user called: ";  
     print $nick_names[$number_of_user];
     print " is arrieved.\n";
     $number_of_user=$number_of_user+1;
    }
   }
   else
   {
    ## Implementation of fourth step of the protocol: "Sendidng ERROR/OK to client".
    $new_sock->send("ERR The second message that must be sent to the server is Nickname!");
    $readable_handles->remove($new_sock);
	close($new_sock);
   }
  }
  else 
  {
   $sock->recv($receive, 1024);
   my @sockets = $readable_handles->can_write();
   $length=length($receive);
   if($length>255)
   {
    $sock->send("ERR The message should not be longer than 255 characters, pleas try again\n");
   }
   else
   { 
    for ($i=0;$i<=$number_of_user;$i++)
    {
     if ($sock eq $sockets[$i])
     {
      $current_user_number = $i; 
     }
    }
    $receive=substr $receive, 4;
    $receive= "".$nick_names[$current_user_number]." ".$receive."";
    $receive = "MSG".$receive.""; 
    foreach my $sck (@sockets) 
    {
     $sck->send($receive);
    }
   } 
  } 
 } 
} 






