#!/usr/bin/perl

use WWW::Mechanize;

die "Usage: ss_submit ProblemID filename\n" unless $#ARGV == 1;

open IN, "<$ARGV[1]" || die "Cannot open file '$ARGV[1]'";
$data = join "", <IN>;
close IN;

select STDOUT; $| = 1;

my $url = "http://acm.uva.es/problemset/submit.php";
my $mech = WWW::Mechanize->new();

print "Obtaining form page... ";
$mech->get ($url);

die "failed\n" unless $mech->success ();
print "done\n";

print "Submit problem... ";

$mech->submit_form (
    form_number => 1,
    fields => {
        problem  => $ARGV[0],
        language => "C++",
        userid => "4200CH",
        code => $data,
    }                
);

die "failed\n" unless $mech->success ();
print "done\n";

`opera -newpage http://acm.uva.es/problemset/statusjudge.php`

