
function setnumbers()
{
let start = document.querySelector('#first_num').value;
let finish = document.querySelector('#last_num').value;

// if not activate an alarm
if (start ==='')
{
alert("Please enter the first number")
}
else if (finish ==='')
{
                    alert("Please enter the last number")
                }

                if (finish < start)
                {
                    alert("first number must be smaller than last")
                }
                else
                {
                    temp = '<tr><th>Start</th><th>Finish</th><th>Difference</th></tr>';
                    for (i = start; i <= finish; i++)
                    {
                        diff = finish - i;
                        document.querySelector('#rightcol').innerHTML = '<tr>'+ temp + '<td>' + i + '</td>' +'<td>' + finish + '</td>'+
                        '<td>' + diff + '</td></tr>';

                        temp = document.querySelector('#rightcol').innerHTML;
                    }
                }
            }
