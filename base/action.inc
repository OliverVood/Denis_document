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

	Class Action extends ActionOutside {
		public string $area;
		public string $part;

		private string $path;
		private string $href;
		private string $xhr;

		public function __construct(string $area = 'null', string $part = 'null', string $href = '', string $click = '') {
			parent::__construct('', $click);

			$this->area 		= $area;
			$this->part 		= $part;

			$this->path			= '';
			if ($this->area !== 'null') $this->path .= "/{$this->area}";
			if ($this->part !== 'null') $this->path .= "/{$this->part}";

			if ($href == 'default') {
				$this->href 	= REQUEST . $this->path;
				$this->xhr 		= XHR . $this->path;
				$this->address 	= ADDRESS . REQUEST . $this->path;
			} else {
				$this->href 	= REQUEST . $href;
				$this->xhr		= XHR . $href;
				$this->address	= ADDRESS . REQUEST . $href;
			}
		}

		/**
		 * Возвращает path
		 * @return string
		 */
		public function GetPath(): string {
			return $this->path;
		}

		/**
		 * Возвращает href
		 * @param array $data - Данные для замены
		 * @return string
		 */
		public function GetHref(array $data = []): string {
			return $this->ParseTarget($this->href, $data);
		}

		/**
		 * Возвращает xhr
		 * @param array $data - Данные для замены
		 * @return string
		 */
		public function GetXHR(array $data = []): string {
			return $this->ParseTarget($this->xhr, $data);
		}

		/**
		 * Возвращает ссылку для href
		 * @param string $content - Контент
		 * @param array $data - Данные для замены
		 * @param array $params - Параметры
		 * @return string
		 */
		public function GetLinkHref(string $content, array $data = [], array $params = []): string {
			return $this->GetLink($this->GetHref($data), $content, $data, $params);
		}

		/**
		 * Возвращает ссылку для xhr
		 * @param string $content - Контент
		 * @param array $data - Данные для замены
		 * @param array $params - Параметры
		 * @return string
		 */
		public function GetLinkXHR(string $content, array $data = [], array $params = []): string {
			return $this->GetLink($this->GetXHR($data), $content, $data, $params);
		}

		/**
		 * Замена истории
		 * @param array $data - Данные для замены
		 * @return string
		 */
		public function GetHistoryReplace(array $data =[]): string {
			return /** @lang JavaScript */ "Base.Common.History.Replace('{$this->GetHref($data)}', '{$this->GetXHR($data)}');";
		}

	}