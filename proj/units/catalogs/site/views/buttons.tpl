<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\View;
	use Proj\Site\Units\Catalogs;

	class Buttons extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?>
			<div class = "view catalogs buttons">
				<?= Catalogs::instance()->action_estimate->GetLink('Сметы', [], ['class' => 'button img']); ?>
				<?= Catalogs::instance()->action_certificate->GetLink('Акты выполненных работ', [], ['class' => 'button img']); ?>
				<?= Catalogs::instance()->action_price_list->GetLink('Прайс-листы', [], ['class' => 'button img']); ?>
			</div>
		<?php }

	}