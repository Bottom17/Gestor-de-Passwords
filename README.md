# Gestor-de-Passwords
O objetivo deste programa é de simular um gerenciador de palavras-passe como os que existem nos browsers.
Este gerenciador de palavras-passe é executado num terminal e não tem interface como os que existem nos browsers.

# Funcionalidades
Na v1.1 o utilizador pode adicionar as credenciais para um dado site, visualizar essas mesmas credenciais de duas maneiras diferentes (através de uma lista ou simplesmente inserindo o nome do site) e sair do programa.

# Funcionamento
Todos os dados são armazenados em ficheiros, e todos os dados são encriptados exceto o nome do site.
Quando o programa é executado pela primeira vez, o utilizador começa por inserir uma chave mestra que permite encriptar e desencriptar as credenciais.
Cada vez que o programa for executado o utilizador terá de inserir a chave mestra. Em seguida, o utilizador só tem que seguir as instruções dados pelo output do programa.

# Particularidade do programa
Visto que este programa é pouco seguro e que terceiros podem facilmente aceder ao ficheiro no qual os dados encriptados estão armazenados, decidi fazer algo diferente.
A particularidade deste programa é que a chave mestra não é armazenada em sitio algum. Ou seja, o programa em si não compara a chave mestra inserida pela primeira vez que o programa foi executado com a chave mestra inserida nas próximas vezes. 
A vantagem é que terceiros não vão conseguir descobrir a chave mestra visto que não está armazenada em ficheiro algum e consequentemente vão ter muitas dificuldades em desencriptar os dados. A desvantagem é que se o utilizador se esquecer ou digitar mal a chave mestra os dados fornecidos pelo programa vão ser incorretos.

# Por vir
Seria engraçado criar uma funcionalidade que permita ao utilizador de gerar uma palavra-passe aleatória para um determinado site.
Seria igualmente útil o programa perguntar ao utilizador se deseja copiar para a área de transferência do sistema a palavra-passe de um determinado site para o qual o utilizador procurou as credenciais.


