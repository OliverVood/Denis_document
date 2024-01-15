<?php

	namespace Base;

	class ActionOutside {
		protected string $address;
		protected string $click;

		public function __construct(string $address = '', string $click = '') {
			$this->address 	= $address;
			$this->click 	= $click;
		}

		/**
		 * Возвращает address
		 * @param array $data - Параметры
		 * @return string
		 */
		public function GetAddress(array $data = []): string {
			return $this->ParseTarget($this->address, $data);
		}

		/**
		 * Возвращает click
		 * @param array $data - Параметры
		 * @return string
		 */
		public function GetClick(array $data = []): string {
			return $this->ParseTarget($this->click, $data);
		}

		/**
		 * Возвращает ссылку
		 * @param string $href - href
		 * @param string $content - Контент
		 * @param array $data - Параметры
		 * @param array $params - Параметры
		 * @return string
		 */
		protected function GetLink(string $href, string $content, array $data = [], array $params = []): string {
			$href = ' href = "' . $href . '"';
			$onclick = ' onclick = "' . $this->GetClick($data) . '"';
			$class = (isset($params['class'])) ? ' class = "' . $params['class'] . '"' : '';
			$target = (isset($params['target'])) ? ' target = "' . $params['target'] . '"' : '';

			return "<a{$href}{$onclick}{$target}{$class}>{$content}</a>";
		}

		/**
		 * Возвращает ссылку с адресом
		 * @param string $content - Контент
		 * @param array $data - Параметры
		 * @param array $params - Параметры
		 * @return string
		 */
		public function GetLinkAddress(string $content, array $data = [], array $params = []): string {
			return $this->GetLink($this->GetAddress($data), $content, $data, $params);
		}

		/**
		 * Замена параметров в строке
		 * @param string $subject - Строка
		 * @param array  $replace - Массив замен
		 * @return string
		 */
		protected function ParseTarget(string $subject, array $replace): string {
			foreach ($replace as $key => $value) $subject = str_replace("%{$key}%", $value, $subject);

			return  $subject;
		}

	}