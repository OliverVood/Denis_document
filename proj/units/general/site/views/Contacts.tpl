<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\View;
	use Proj\Site\Params;
	use Proj\Site\Units\General;

	class Contacts extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render(): void { ?>
			<div class = "view general contacts">
				<p><?= Params::$site_address; ?> – это молодой, развивающийся проект, который нуждается в Вашей <?= General::instance()->donations->GetLink('доброй поддержке', [], ['class' => 'link']); ?>, здоровой критике и пожеланиях по дальнейшему улучшению.</p>
				<p>По всем вопросам можно обратиться по электронному адресу: <b><?= Params::$support; ?></b>.</p>
			</div>
		<?php }

	}