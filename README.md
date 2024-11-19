## O objetivo do projeto

O projeto Exchange de Criptomoedas tem o objetivo simular contas de usuários e suas movimentações financeiras envolvendo as Criptomoedas como Bitcoin, Etherium e Ripple. O programa realiza transações fictícias como por exemplo a compra, a venda, o depósito e o saque proporcionando dessa maneira uma vivência mais realista dessas operações.

## A forma de compilação e execução
Para executar o programa do Investidor:
    1. Navegue até o diretório onde estão localizados os arquivos do projeto
    2. Para compilar, realize o comando:  gcc investidor.c -o cripto -w
    3. Após a compilação, execute o programa com o comando:  ./cripto  

Para executar o programa do Administrador:
    1. Navegue até o diretório onde estão localizados os arquivos do projeto
    2. Para compilar, realize o comando:  gcc administrador.c -o adm -w
    3. Após a compilação, execute o programa com o comando:  ./adm

 Nota: É primordial ter instalado o gcc para poder executar ambos os programas.


## Uma breve explicação sobre a forma de uso do programa

Programa do Investidor:

    Ao iniciar o programa, o usuário deve informar seu CPF e senha para realizar o login. Em seguida, o sistema verifica se o CPF e a senha correspondem a um usuário investidor registrado no arquivo usuarios.bin. Caso a autenticação seja bem-sucedida, o usuário terá acesso ao menu principal, onde poderá realizar as seguintes operações:

    Ao digitar "1" o usuário pode visualizar o saldo de reais, Bitcoin, Ethereum e Ripple na carteira de investimentos. Digitando "2" o usuário pode consultar seu histórico de operações realizadas na carteira de investimentos. Digitando "3" pode-se depositar reais na carteira de investimentos. Digitando "4" permite o saque de reais da carteira de investimentos, desde que o valor de saque seja igual ou menor ao saldo na carteira. O "5" possibilita a compra de criptomoedas, utilizando o saldo disponível. O "6" permite a venda de criptomoedas, convertendo-as em reais. E por último, "8", o usuário finaliza a sessão no programa.

 
    Segue lista de usuários e suas respectivas senhas para que o login seja bem-sucedido:
    12345678901-1122
    23456789012-0987
    34567890123-6754
    45678901234-9999
    56789012345-3245
    67890123456-0000
    78901234567-6556
    89012345678-7342
    90123456789-8710
    01234567890-0901 

Programa do Administrador:

    Ao iniciar o programa, o usuário deve informar seu CPF e senha para realizar o login. Em seguida, o sistema verifica se o CPF e a senha correspondem a um usuário de administrador registrado no arquivo administradores.bin. Caso a autenticação seja bem-sucedida, o usuário terá acesso ao menu principal, onde poderá realizar as seguintes operações:

    Ao digitar "1" o administrador pode cadastrar de novos investidores informando nome, CPF e senha. Digitando "2" o administrador pode 
    excluir um investidor, informando o CPF, visualiza os dados cadastrados e confirma a exclusão. Digitando "3" pode-se cadastrar novas criptomoedas informando o nome, cotação inicial, taxa de compra e taxa de venda. Digitando "4" o administrador pode efetuar a exclusão de uma determinada criptomoeda, exibindo os dados da criptomoeda informada e solicitando confirmação antes de excluí-la. O "5" possibilita a visualização do saldo de um investidor ao informar o CPF. O "6" permite a consulta do histórico completo de transações realizadas pelo investidor basta informar o CPF.  O "7" mostra ao usuário a cotação das criptomoedas atualizada. E por último, "8", o usuário finaliza a sessão no programa.

    Segue lista de administradores e suas respectivas senhas para que o login seja bem-sucedido:
    CPF: 11122233344 - Senha: 1234
    CPF: 55566677788 - Senha: 9876

## Lista com os nomes e matrícula dos participantes do grupo
- Luanna P. Gonçalves  22.124.044-3
- Lucas Masashi Yamashiro  22.124.047-6

