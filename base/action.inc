<?php

	namespace Base;

	Class Action {
		public string $area;
		public string $part;

		public string $path;
		private string $href;
		private string $click;

		public function __construct(string $area = 'null', string $part = 'null', string $href = '', string $click = '') {
			$this->area 	= $area;
			$this->part 	= $part;

			$this->href 	= REQUEST . $href;
			$this->click 	= $click;

			$this->path		= '';
			if ($this->area !== 'null') $this->path .= "/{$this->area}";
			if ($this->part !== 'null') $this->path .= "/{$this->part}";

			if ($href == 'default') $this->href = REQUEST . $this->path;
		}

		/**
		 * Возвращает ссылку
		 * @param string $content - Контент
		 * @param array $data - Параметры
		 * @param array $params - Параметры
		 * @return string
		 */
		public function GetLink(string $content, array $data = [], array $params = []): string {
			$href = ' href = "' . $this->GetHref($data) . '"';
			$onclick = ' onclick = "' . $this->GetClick($data) . '"';
			$class = (isset($params['class'])) ? ' class = "' . $params['class'] . '"' : '';
			$target = (isset($params['target'])) ? ' target = "' . $params['target'] . '"' : '';

			return "<a{$href}{$onclick}{$target}{$class}>{$content}</a>";
		}

		/**
		 * Возвращает href
		 * @return string
		 */
		public function GetPath(): string {
			return $this->path;
		}

		/**
		 * Возвращает href
		 * @param array $data - Параметры
		 * @return string
		 */
		public function GetHref(array $data = []): string {
			return $this->ParseTarget($this->href, $data);
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
		 * Замена параметров в строке
		 * @param string $subject - Строка
		 * @param array  $replace - Массив замен
		 * @return string
		 */
		private function ParseTarget(string $subject, array $replace): string {
			foreach ($replace as $key => $value) $subject = str_replace("%{$key}%", $value, $subject);

			return  $subject;
		}

	}