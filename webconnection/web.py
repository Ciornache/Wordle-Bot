from asyncio.windows_events import NULL
import email
from email.parser import BytesParser
from hashlib import pbkdf2_hmac
from hmac import new
from http.client import NETWORK_AUTHENTICATION_REQUIRED
from multiprocessing.connection import wait
from telnetlib import LOGOUT
from selenium import webdriver
from time import sleep
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.wait import WebDriverWait
from selenium.common.exceptions import NoSuchElementException,  NoSuchWindowException, TimeoutException, StaleElementReferenceException
from selenium.webdriver.common.keys import Keys
import json
import pyautogui
from selenium.webdriver.common.action_chains import ActionChains
import asyncio
import threading
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities


f = open("configs/candidate.txt", "r")

word = f.read()

driver = webdriver.Chrome(executable_path= "webconnection/chromedriver1.exe")

def uploadWord():
    driver.get("https://wordlegame.org/")
    for letter in word:
        pyautogui.press(letter)


uploadWord()
