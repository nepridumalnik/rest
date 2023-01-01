$Uri = 'localhost'

$body = @{
      name='username'
      password='userpassword'
}

$contentType = 'application/x-www-form-urlencoded' 

Invoke-WebRequest -Method POST -Uri $Uri -body $body -ContentType $contentType
