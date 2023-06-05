<?php

	namespace Base\Editor\Skins\Browse;

	use Base\Editor\Skins\SkinBrowse;

	class DateFormat extends SkinBrowse {
		private string $format;

		public function __construct(string $title, string $format) {
			parent::__construct($title);

			$this->format = $format;
		}

		public function ToVar(mixed $value): string {
			try {
				$date = date_format(new \DateTime($value), $this->format);
			} catch (\Exception) {
				$date = '';
			}

			return $date;
		}

	}