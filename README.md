# boggle_server_starter

Program structure and starter code for boggle server (Homework IV).


Run <code>./demo_server</code> to see the desired behavior of the server.


In a separate terminal, connect to server with netcat:
<pre><code>nc -C localhost 8888</code>
</pre>

Test the following commands
<pre>
<code>new_game</code>
<code>add_score</code>
</pre>

On several separate terminals, run netcat for each new client, run <code>new_game</code>, 
<code>add_score</code> and then test with:

<pre>
<code>all_players</code>
<code>top_3</code>
</pre>