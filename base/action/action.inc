<?php

	namespace Base;

	class Action extends ActionOutside {
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
			return $this->ParseTarget($this->href ?: '/', $data);
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
