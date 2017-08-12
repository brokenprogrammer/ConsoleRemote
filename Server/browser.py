import selenium
from selenium import webdriver
from selenium.webdriver.firefox.firefox_binary import FirefoxBinary

binary = FirefoxBinary(r"C:\Program Files (x86)\Mozilla Firefox\firefox.exe")
fp = webdriver.FirefoxProfile()
driver = webdriver.Firefox(firefox_binary=binary, firefox_profile=fp, executable_path="C:\Program Files (x86)\Mozilla Firefox\geckodriver.exe")

driver.get("http://www.google.com")


