//Mastercard Payment Verification Begins
//Executes the JavaScript after page has been loaded
window.onload=()=>{
	const btn = document.getElementById('submit')
	btn.addEventListener('click', dosth)
	function dosth(e){
		e.preventDefault()
		
		//Gets the inputs
		let ind = 1 //0 for false 1 for true
		const n = document.getElementById('ccn').value
		const m = document.getElementById('m').value
		const y = document.getElementById('y').value
		const cvv = document.getElementById('cvv').value
		const data = {
		 "master_card": parseInt(n),
		 "exp_year": parseInt(y),
		 "exp_month": parseInt(m),
		 "cvv_code": cvv
		 }
		//Console.table(data)

		//Payment Validation (Uses Regex Values for each part)
		re = /^5[1-5][0-9]{14}/
		if(!n.match(re)) {
			ind = 0
			alert('Wrong Card Number entered, Please try again')	
		}

		re_cvv = /[0-9]{3,4}/
		if(!cvv.match(re_cvv)) {
			ind = 0
			alert('Wrong CVV Code entered, Please try again')	
		}

		const url = 'https://mudfoot.doc.stu.mmu.ac.uk/node/api/creditcard'

		//Sends values to API if Valid
		if(ind) {
			fetch(url, {
				method: "post",
				headers: {
					"Content-Type": "application/json"
				},
				body: JSON.stringify(data)
			})

			.then((response)=>{
				if(response.status === 200){
					return response.json()
				}else if(response.status === 400){
					throw 'Bad'
				}else throw 'Bad others'
			})

			.then((resJson)=>{
				alert(resJson['message'])
				window.location.href='success.html'
			})

			.catch((err)=>{
				alert(err)
			})
		}
	}
}
// Payment Verification Ends